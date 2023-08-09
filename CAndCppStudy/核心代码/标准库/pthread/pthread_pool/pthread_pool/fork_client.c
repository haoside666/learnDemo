#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

#define PORT_TCP 9001

int main(int argc, char *argv[])
{
    int sockfd;
    char buffer[1024];
    int length;
    int iSendLen;
    unsigned char ucSendBuf[1024];
    struct hostent *host;
    struct sockaddr_in server_addr; //ftp addr
    if (argc != 2)
    {
        printf("./%s hostname \n", argv[0]);
        exit(0);
    }
    //���û������IP��ַ����ת��
    if ((host = gethostbyname(argv[1])) == NULL)
    {
        exit(1);
    }
    //�����ͻ��˵�SOCKET����
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        exit(1);
    }

    //���ô����õ�socket
    //����socket addr������
    bzero(&server_addr, sizeof(struct sockaddr_in)); //��ʼ��Ϊ0
    server_addr.sin_family = AF_INET;                //����IPV4Э����
    //���Ҫ���õ�ַ�Ͷ˿ںţ�����ת��Ϊ�����ֽ���
    server_addr.sin_addr = *((struct in_addr *)host->h_addr); //ip��ַ
                                                              //server_addr.sin_addr.s_addr=inet_addr("192.168.1.1");
    server_addr.sin_port = htons(PORT_TCP);

    if (connect(sockfd, (struct sockaddr *)(&server_addr), sizeof(struct sockaddr)) == -1)
    {
        exit(1);
    }

    while (1)
    {
        //��ÿͻ��˱�׼������ַ�������
        if (fgets(ucSendBuf, 1000, stdin))
        {
            iSendLen = send(sockfd, ucSendBuf, strlen(ucSendBuf), 0);
            if (iSendLen <= 0)
            {
                close(sockfd);
                exit(0);
            }
        }
        length = read(sockfd, buffer, 1000);
        if (length)
        {
            buffer[length] = '\0';
            printf("received  from ftp :%s\n", buffer);
            length = 0;
        }
    }
}
