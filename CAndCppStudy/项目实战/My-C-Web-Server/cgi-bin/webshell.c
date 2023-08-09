#include "wrap.h"
#include "parse.h"
#include <unistd.h>
char tempfile[256]="/tmp/temp.txt";
char rmtempfile[256]="rm /tmp/temp.txt";
char *cwd;
int bash_handler(char *command,char *content);
void replace_blank(char *dest,char *src);
void replace(char *dest,char *src);


int main(void) 
{
    char *cmd,content[MAXBUF*128],command[MAXBUF];
    int sava_fd;
    /* Extract the two arguments */
    cmd= getenv("QUERY_STRING")+8;
    cwd=getenv("CURRENT_PATH");
    replace_blank(command,cmd);
    sprintf(content,"input command:%s\n<br>",command);
    sava_fd=dup(STDOUT_FILENO);  
    if(bash_handler(command,content)<0)
    {
        sprintf(content, "%serror occurred\r\n", content);
    }
    dup2(sava_fd, STDOUT_FILENO);
    /* Generate the HTTP response */
    printf("Content-length: %ld\r\n", strlen(content));
    printf("Content-type: text/html\r\n\r\n");
    printf("%s", content);
    fflush(stdout);
    if (access(tempfile, F_OK) == 0)
    {
        system(rmtempfile);
    }
    return 0;
}

void replace(char *dest,char *src)
{
    int i=0,j=0;
    while(src[i]!='\0')
    {
        if(src[i]=='\n')
        {
            dest[j++]='<';
            dest[j++]='b';
            dest[j++]='r';
            dest[j]='>';
        }else
        {
            dest[j]=src[i];
        }
        i++;j++;
    }
}
void replace_blank(char *dest,char *src)
{
    int i=0,j=0;
    while(src[i]!='\0')
    {
        if(src[i]=='+')
        {
            dest[j]=' ';
        }else
        {
            dest[j]=src[i];
        }
        i++;j++;
    }
}


int bash_handler(char *command,char* content)
{
    int fd,len;
    char temp_buf[MAXBUF],current_path[MAXBUF],dest_buf[MAXBUF];
    getcwd(current_path,MAXBUF);
    sprintf(content, "%scurrent_work_path:%s\r\n<br>", content,current_path);
//    if(strstr(current_path,cwd)==NULL)
//    {
//        sprintf(content, "%s Permission denied.<br>", content);
//        sprintf(content, "%s The directory should be a subdirectory or subfile of %s", content,cwd);
//        return 0;
//    }
     if (access(tempfile, F_OK) == 0)
    {
        fd = open(tempfile, O_TRUNC | O_WRONLY);
    }
    else
    {
        fd = open(tempfile, O_CREAT | O_TRUNC | O_WRONLY, 0666);
    }
    if (fd < 0)
    {
        return -1;
    }
    dup2(fd, 1);
    dup2(fd, 2);
    system(command);
    close(fd);
    fd = open(tempfile, O_RDONLY);
    if (fd < 0)
    {
        return -1;
    }
    sprintf(content, "%s read content:", content);
    while ((len = read(fd, temp_buf, MAXBUF)))
    {
        if (len == -1)
        {
            return -1;
        }
        else
        {         
            replace(dest_buf,temp_buf);
            sprintf(content, "%s%s\r\n", content,dest_buf);
        }
    }
    return 0;
}
