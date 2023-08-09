#define _XOPEN_SOURCE 600
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <aio.h>
#include <semaphore.h>
#include <ftw.h>
#include <dirent.h>
#include <errno.h>
#include <time.h>
#include <strings.h>
#define MAX_PATH 256
#define FD_MAX 1024

size_t buffer_size;          
uint64_t  page_size;         
int lock_num_requests;

sem_t blocking_waiter;

char src[MAX_PATH];
char dst[MAX_PATH];

void aio_read_handler (sigval_t  sigval);
void aio_write_handler(sigval_t signal);
char *format_path(char* path) ;
char* Find_Last_dir_Path(char * path);
int is_equal_dir(char* _src,char* _dst);
static int tree_walk(const char *fpath, const struct stat *sb,int tflag, struct FTW *ftwbuf);

typedef struct handler_context
{
    struct aiocb* m_aiocb;      
    size_t m_offset;            
    size_t m_file_size;         
    int m_src_fd;              
    int m_dst_fd;              
} handler_context;


void aio_read_handler (sigval_t  sigval)
{
    size_t nbytes;
    size_t w_nbytes = 0;
    handler_context* hctx = (handler_context*)sigval.sival_ptr;
    
    nbytes = aio_return(hctx->m_aiocb);
    int i = 0;
    void * buffer = (void *)hctx->m_aiocb->aio_buf;
    
    struct aiocb*  w_aiocb = (struct aiocb*)malloc(sizeof(struct aiocb));
    handler_context* w_context = (handler_context *) malloc(sizeof(handler_context));
    bzero ((char *)w_context, sizeof(handler_context));
    bzero ((char *)w_aiocb, sizeof(struct aiocb));
    
    // context to be passed to handler
    w_context->m_aiocb = w_aiocb;
    w_context->m_offset = hctx->m_offset;
    w_context->m_file_size = hctx->m_file_size;
    w_context->m_src_fd = hctx->m_src_fd;
    w_context->m_dst_fd = hctx->m_dst_fd;

    // basic setup
    w_aiocb->aio_fildes = hctx->m_dst_fd;
    w_aiocb->aio_nbytes = nbytes;
    w_aiocb->aio_offset = hctx->m_offset;
    w_aiocb->aio_buf = buffer;

    // thread callback
    w_aiocb->aio_sigevent.sigev_notify = SIGEV_THREAD;
    w_aiocb->aio_sigevent.sigev_notify_function = aio_write_handler;
    w_aiocb->aio_sigevent.sigev_notify_attributes = NULL;
    w_aiocb->aio_sigevent.sigev_value.sival_ptr = (void *)w_context;

    if (aio_write(w_aiocb) < 0) 
    {
        perror("aio_write error");
        exit(-1);
    }
    ++lock_num_requests;
    sem_post(&blocking_waiter);
    free(hctx);
}

void aio_write_handler (sigval_t sigval)
{
    size_t nbytes;
    handler_context* hctx = (handler_context*)sigval.sival_ptr;

    nbytes = aio_return(hctx->m_aiocb);
    sem_post(&blocking_waiter);
    free((void *)hctx->m_aiocb->aio_buf); 
    hctx->m_aiocb->aio_buf =NULL;           
    close(hctx->m_src_fd);
    close(hctx->m_dst_fd);
    free(hctx);
}

int copy_regular (const char* src_file, const char* dst_file)
{
    
    int src_fd;
    int dst_fd;
    
    uint64_t num_pages;
    void * buffer_block;
       
    page_size = getpagesize();
    
    struct stat stat_buf, stat_dst;
    // stat the source file
    if (stat(src_file, &stat_buf) == -1 ) 
    {
        perror("source file stat error");
        exit(-1);
    }
    
    if ((src_fd = open(src_file, O_RDONLY)) < 0) 
    {
        perror("source file open error");
        exit(-1);
    }
    
    if ((dst_fd = open(dst_file, O_WRONLY| O_CREAT|O_TRUNC, stat_buf.st_mode)) < 0) 
    {
        perror("destination file open error");
        exit(-1);
    }
    
    if (fstat(dst_fd, &stat_dst) == -1) 
    {
        perror("fstat destination error");
        exit(-1);
    }
    
   
    if (stat_buf.st_dev  == stat_dst.st_dev && \
        stat_buf.st_ino == stat_dst.st_ino)
        return 0;
  
    // TODO tell the kernel that we will need the input file
    posix_fadvise(src_fd, 0, stat_buf.st_size, POSIX_FADV_WILLNEED);
  
    // more efficient space allocation via fallocate for dst file
    //if (fallocate(dst_fd, 0, 0, stat_buf.st_size) == -1) 
    //    printf("%s\n",strerror(errno));
    if (lseek(dst_fd, stat_buf.st_size-1, SEEK_SET) == -1) 
        printf("%s\n",strerror(errno));
    write(dst_fd,"",1);
    lseek(dst_fd, 0, SEEK_SET);

    // decide the number of pages in the input file and malloc a buffer accordingly
    num_pages = stat_buf.st_size / page_size + 1;
    buffer_size = page_size; 
    //(num_pages < BUF_MAX) ? (num_pages * page_size) : (BUF_MAX * page_size);

    // now start sending aio read requests
    size_t i;
    for (i = 0; i < stat_buf.st_size; i += buffer_size)
    {
        //posix_fadvise(src_fd, i, buffer_size, POSIX_FADV_SEQUENTIAL);
        buffer_block = (void *)malloc(buffer_size);
        if (errno == ENOMEM) 
        {
            perror("malloc for buffer error");
            exit(-1);
        }  
        // init aiocb struct
        struct aiocb* r_aiocb = (struct aiocb*)malloc(sizeof(struct aiocb));
        handler_context* r_context = (handler_context *) malloc(sizeof(handler_context));
        bzero ((char *)r_context, sizeof(handler_context));
        bzero ((char *)r_aiocb, sizeof(struct aiocb));
        
        // context to be passed to handler
        r_context->m_aiocb = r_aiocb;
        r_context->m_offset = i;
        r_context->m_file_size = stat_buf.st_size;
        r_context->m_src_fd = src_fd;
        r_context->m_dst_fd = dst_fd;

        // basic setup
        r_aiocb->aio_fildes = src_fd;
        r_aiocb->aio_nbytes = buffer_size;
        r_aiocb->aio_offset = i;
        r_aiocb->aio_buf = buffer_block;

        // thread callback
        r_aiocb->aio_sigevent.sigev_notify = SIGEV_THREAD;
        r_aiocb->aio_sigevent.sigev_notify_function = aio_read_handler;
        r_aiocb->aio_sigevent.sigev_notify_attributes = NULL;
        r_aiocb->aio_sigevent.sigev_value.sival_ptr = (void *)r_context;

        if (aio_read(r_aiocb) < 0) 
        {
            perror("aio_read error");
            exit(-1);
        }
        ++lock_num_requests;
    } 
    return 0;
}

int main(int argc, char * argv[])
{
    if (argc != 3)
    {
        printf("usage : %s <source> <destination>\n.", argv[0]);
        return 0;
    }
    
    struct timespec tv1, tv2;
    lock_num_requests = 0;
    
    clock_gettime(CLOCK_MONOTONIC, &tv1);
    
    sem_init(&blocking_waiter, 0, 0);
    uint64_t i;
    
    strcpy(src,argv[1]);
    strcpy(dst,argv[2]);
    if(src[strlen(src)-1]=='/')
        src[strlen(src)-1]='\0';
    if(dst[strlen(dst)-1]=='/')
        dst[strlen(dst)-1]='\0';

    struct stat src_stat, dst_stat;
    if (stat(src, &src_stat) == -1)
    {
        perror("source file stat error");
        exit(-1);
    }
       
    if (stat(dst, &dst_stat) == -1)     
    {       
        perror("destination file stat error");
        exit(-1);        
    }

    if (S_ISDIR(src_stat.st_mode)) 
    {
        if(!S_ISDIR(dst_stat.st_mode))
        {
            perror("cannot copy directory to non-directory");
            exit(-1);
        }
        int iRet = is_equal_dir(src,dst);
        if ( iRet == 1)
        {
            printf("the dest alread exist the same directory.\n");
            if (nftw(src, tree_walk, FD_MAX, 0))
            {
                perror("nftw traversal error");
                exit(-1);
            }
        }
        else
        {      
            char* dirname=Find_Last_dir_Path(src);            
            sprintf(dst,"%s/%s",dst,dirname);
            if(mkdir(dst, S_IRWXU | S_IRWXG) == -1)
            {
                perror("destination mkdir failed");
                exit(-1);
            }            
            free(dirname);
            if (nftw(src, tree_walk, FD_MAX, 0))
            {
                perror("nftw traversal error");
                exit(-1);
            }
        } 
    }
    else  
    {
        if(!S_ISDIR(dst_stat.st_mode))
        {
            copy_regular(src, dst);
        }else
        {
            char* dirname=Find_Last_dir_Path(src);  
            sprintf(dst,"%s/%s",dst,dirname);
            free(dirname);
            copy_regular(src, dst);
        }      
    }
    for (i = 0; i < lock_num_requests; ++i) 
    {
        sem_wait(&blocking_waiter);
    }
    
    sem_destroy(&blocking_waiter);
    clock_gettime(CLOCK_MONOTONIC, &tv2);
    uint64_t tv = (tv2.tv_sec - tv1.tv_sec) * 1000000000+ tv2.tv_nsec -tv1.tv_nsec;
    printf("completion time = %ld.%06ld s\n", tv / 1000000000, tv % 1000000000);
    return 0;
}

char* Find_Last_dir_Path(char * path)
{
	char *temp = (char*)malloc(strlen(path)+1);
	strcpy(temp,path);
	int i = 0;
	for(i = strlen(temp) - 1;i>=0 ;i--)
	{
		if(temp[i] == '/')
			break;
	}
    if(i==-1)
    {
        return temp;
    }else
    {
        temp[i]=0;
        char *result = (char*)malloc(strlen(&temp[i + 1])+1);
        strcpy(result,&temp[i + 1]);
        free(temp);
        return result;
    }
}

int is_equal_dir(char* _src,char* _dst)
{    
    char *p=Find_Last_dir_Path(_src);
    char *q=Find_Last_dir_Path(_dst);
    if(strcmp(p,q))
    {
        free(p);
        free(q);
        return 0;
    }else
    {
        free(p);
        free(q);
        return 1;
    }    
}

static int tree_walk(const char *fpath, const struct stat *sb,int tflag, struct FTW *ftwbuf)
{
	if(strcmp(fpath,src)==0) return 0;
    char new_dst_path[MAX_PATH];
	sprintf(new_dst_path,"%s/%s",dst, fpath+strlen(src)+1);
	if(tflag == FTW_D)
	{
		if(mkdir(new_dst_path, S_IRWXU | S_IRWXG) == -1)
        {
            perror("destination mkdir failed");
            exit(-1);
        }     
	}else
	{           
    	copy_regular(fpath, new_dst_path);
	}  
    return 0;
}
