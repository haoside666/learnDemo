/******************************************************************************
*
*  Copyright (C), 2020-2025, haoside
*
*******************************************************************************
*  File Name     : pub.c
*  Version       : Initial Draft
*  Author        : haoside
*  Created       : 2020/9/6
*  Last Modified :
*  Description   : 
*  Function List :
*
*       1.                get_filetype
*       2.                get_file_content
*       3.                save_log
*       4.                setdaemon
*       5.                socket_accept
*       6.                socket_create
*
*  History:
* 
*       1.  Date         : 2020/9/6
*           Author       : haoside
*           Modification : Created file
*
******************************************************************************/
#include"pub.h"
/*****************************************************************************
*   Prototype    : save_log
*   Description  : save message to log
*   Input        : char *buf  
*   Output       : None
*   Return Value : void
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/9/6
*           Author       : haoside
*           Modification : Created function
*
*****************************************************************************/
void save_log(char *buf)
{
      FILE *fp = fopen("log.txt","a+");  
      fputs(buf,fp);  
      fclose(fp);  
}

/*****************************************************************************
*   Prototype    : setdaemon
*   Description  : set daemon peocess
*   Input        : None
*   Output       : None
*   Return Value : void
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/9/6
*           Author       : haoside
*           Modification : Created function
*
*****************************************************************************/
void setdaemon() 
{
	pid_t pid, sid;
	pid = fork();
	if (pid < 0)
	{
		memset(LOGBUF,0,sizeof(LOGBUF));
		sprintf(LOGBUF,"[-] %s,%d:fork failed %s\n", __FILE__, __LINE__,strerror(errno));
		save_log(LOGBUF);
		exit (EXIT_FAILURE);
	}
	if (pid > 0)
	{
		exit (EXIT_SUCCESS);
	}

	if ((sid = setsid()) < 0)
	{
		memset(LOGBUF,0,sizeof(LOGBUF));
		sprintf(LOGBUF,"[-] %s,%d:setsid failed %s\n", __FILE__, __LINE__,strerror(errno));
		save_log(LOGBUF);
		exit (EXIT_FAILURE);
	}
  /*if (chdir("/") < 0)
	 {
	    memset(LOGBUF,0,sizeof(LOGBUF));
		sprintf(LOGBUF,"[-] %s,%d:chdir failed %s\n", __FILE__, __LINE__,strerror(errno));
		save_log(LOGBUF);
		exit (EXIT_FAILURE);
	 }*/
	 umask(0);
	 close(STDIN_FILENO);
	 close(STDOUT_FILENO);
	 close(STDERR_FILENO);

}

const char *get_filetype(const char *filename) 
{
	char sExt[32];
	const char *p_start=filename;
	memset(sExt, 0, sizeof(sExt));
	while(*p_start)
	{
		if (*p_start == '.')
		{
			p_start++;
			strncpy(sExt, p_start, sizeof(sExt));
			break;
		}
		p_start++;
	}


	if (strncmp(sExt, "bmp", 3) == 0)
		return "image/bmp";

	if (strncmp(sExt, "gif", 3) == 0)
		return "image/gif";

	if (strncmp(sExt, "ico", 3) == 0)
		return "image/x-icon";

	if (strncmp(sExt, "jpg", 3) == 0)
		return "image/jpeg";

	if (strncmp(sExt, "avi", 3) == 0)
		return "video/avi";

	if (strncmp(sExt, "css", 3) == 0)
		return "text/css";

	if (strncmp(sExt, "dll", 3) == 0)
		return "application/x-msdownload";

	if (strncmp(sExt, "exe", 3) == 0)
		return "application/x-msdownload";

	if (strncmp(sExt, "dtd", 3) == 0)
		return "text/xml";

	if (strncmp(sExt, "mp3", 3) == 0)
		return "audio/mp3";

	if (strncmp(sExt, "mpg", 3) == 0)
		return "video/mpg";

	if (strncmp(sExt, "png", 3) == 0)
		return "image/png";

	if (strncmp(sExt, "ppt", 3) == 0)
		return "application/vnd.ms-powerpoint";

	if (strncmp(sExt, "xls", 3) == 0)
		return "application/vnd.ms-excel";

	if (strncmp(sExt, "doc", 3) == 0)
		return "application/msword";

	if (strncmp(sExt, "mp4", 3) == 0)
		return "video/mpeg4";

	if (strncmp(sExt, "ppt", 3) == 0)
		return "application/x-ppt";

	if (strncmp(sExt, "wma", 3) == 0)
		return "audio/x-ms-wma";

	if (strncmp(sExt, "wmv", 3) == 0)
		return "video/x-ms-wmv";

	return "text/html";
}


/*****************************************************************************
*   Prototype    : socket_create
*   Description  : create socket 
*   Input        : int port  
*   Output       : None
*   Return Value : int
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/9/6
*           Author       : haoside
*           Modification : Created function
*
*****************************************************************************/
int socket_create(int port)
{
    memset(LOGBUF,0,sizeof(LOGBUF));
	sprintf(LOGBUF,"**********************************************\n");
    strcat(LOGBUF,"             web server startup               \n");
    strcat(LOGBUF,"**********************************************\n");
	save_log(LOGBUF);
	int st = socket(AF_INET, SOCK_STREAM, 0);
	int on =1;
	if (st == -1)
	{
		memset(LOGBUF,0,sizeof(LOGBUF));
		sprintf(LOGBUF,"[-] %s,%d:socker error %s\n", __FILE__, __LINE__, strerror(errno));
		save_log(LOGBUF);
		return 0;
	}
	if (setsockopt(st, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1)
	{
		memset(LOGBUF,0,sizeof(LOGBUF));
		sprintf(LOGBUF,"[-] %s,%d:setsockopt failed %s\n", __FILE__, __LINE__,strerror(errno));
		save_log(LOGBUF);
		return 0;
	}
	struct sockaddr_in sockaddr;
	memset(&sockaddr, 0, sizeof(sockaddr));
	sockaddr.sin_port = htons(port); 
	sockaddr.sin_family = AF_INET;	
	sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(st, (struct sockaddr *) &sockaddr, sizeof(sockaddr)) == -1)
	{
		memset(LOGBUF,0,sizeof(LOGBUF));
		sprintf(LOGBUF,"[-] %s,%d:bind error %s \n", __FILE__, __LINE__, strerror(errno));
		save_log(LOGBUF);
		return 0;
	}

	if (listen(st, 100) == -1)
	{
		memset(LOGBUF,0,sizeof(LOGBUF));
		sprintf(LOGBUF,"[-] %s,%d:listen failture %s\n", __FILE__, __LINE__,strerror(errno));
		save_log(LOGBUF);
		return 0;
	}
    memset(LOGBUF,0,sizeof(LOGBUF));
	sprintf(LOGBUF,"[+] start server success!\n");
	save_log(LOGBUF);
	return st;

}

int socket_accept(int st)
{
	int client_st;
	struct sockaddr_in client_sockaddr;
	socklen_t len = sizeof(client_sockaddr);

	pthread_t thrd_t;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED); 
	memset(&client_sockaddr, 0, sizeof(client_sockaddr));

	while (1)
	{
		client_st = accept(st, (struct sockaddr *) &client_sockaddr, &len);
		if (client_st == -1)
		{
			memset(LOGBUF,0,sizeof(LOGBUF));
			sprintf(LOGBUF,"[-] %s,%d:accept failture %s \n", __FILE__, __LINE__,strerror(errno));
			save_log(LOGBUF);
			return 0;
		} else
		{
			int *tmp = (int *) malloc(sizeof(int));
			*tmp = client_st;
			pthread_create(&thrd_t, &attr, http_thread, tmp);
		}

	}
}

int  get_file_content(const char *file_name, char **content) 
{
	int  file_length = 0;
	FILE *fp = NULL;

	if (file_name == NULL)
	{
		return file_length;
	}
	fp = fopen(file_name, "rb");

	if (fp == NULL)
	{
		memset(LOGBUF,0,sizeof(LOGBUF));
		sprintf(LOGBUF,"[-] file name: %s,%s,%d:open file failture %s \n",file_name, __FILE__, __LINE__,strerror(errno));
		save_log(LOGBUF);
		return file_length;
	}

	fseek(fp, 0, SEEK_END);
	file_length = ftell(fp);
	rewind(fp);

	*content = (char *) malloc(file_length);
	if (*content == NULL)
	{
		memset(LOGBUF,0,sizeof(LOGBUF));
		sprintf(LOGBUF,"[-] %s,%d:malloc failture %s \n", __FILE__, __LINE__,strerror(errno));
		save_log(LOGBUF);
		return 0;
	}
	fread(*content, file_length, 1, fp);
	fclose(fp);

	return file_length;
}
