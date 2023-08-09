#include"thread_work.h"

/*****************************************************************************
*   Prototype    : get_http_command
*   Description  : Parse the request of http
*   Input        : char *http_msg  
*                  char *command   
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
void get_http_command(char *http_msg, char *command)
{
	char *p_end = http_msg;
	char *p_start = http_msg;
	while (*p_start) //GET /
	{
		if (*p_start == '/')
		{
			break;
		}
		p_start++;
	}
	p_start++;
	p_end = strchr(http_msg, '\n');
	while (p_end != p_start)
	{
		if (*p_end == ' ')
		{
			break;
		}
		p_end--;
	}
	strncpy(command, p_start, p_end - p_start);  //URL

}

void get_http_uac(char *http_msg, char *uac)
{
	char *p_end,*p_start;
	p_start = strstr(http_msg, "User-Agent:")+11;
	p_end = strchr(p_start, '\n');
	strncpy(uac, p_start, p_end - p_start);  //URL
}

void uac_parser(const char* uac)
{
	char *emptylist[] = { NULL };
    if (Fork() == 0)
	{  /* child  */ 
		setenv("QUERY_STRING", uac, 1); 
		execve("uaparser", emptylist, environ); /* Run CGI program */	
	}
}

int make_http_content(const char *command, char **content)
{
	char *file_buf;
	int file_length;
	char headbuf[BUFFSIZE];

	if (command[0] == 0)
	{
		file_length = get_file_content("index.html", &file_buf);
	} else
	{
		file_length = get_file_content(command, &file_buf);
	}
    
	if (file_length == 0)
	{
		return 0;
	}

	memset(headbuf, 0, sizeof(headbuf));
	sprintf(headbuf, HEAD, get_filetype(command), file_length); 

	int iheadlen = strlen(headbuf); 
	int itaillen = strlen(TAIL); 
	int isumlen = iheadlen + file_length + itaillen; 
	*content = (char *) malloc(isumlen); 
	if(*content==NULL)
	{
		memset(LOGBUF,0,sizeof(LOGBUF));
		sprintf(LOGBUF,"[-] %s,%d:malloc failed %s\n", __FILE__,__LINE__,strerror(errno));
		save_log(LOGBUF);
	}
	char *tmp = *content;
	memcpy(tmp, headbuf, iheadlen); 
	memcpy(&tmp[iheadlen], file_buf, file_length); 
	memcpy(&tmp[iheadlen] + file_length, TAIL, itaillen); ;
	if (file_buf)
	{
		free(file_buf);
	}
	return isumlen; 
}


void *http_thread(void *argc)
{
	if(argc==NULL)
	{
		return NULL;
	}
	int st = *(int *) argc;
	free((int *)argc);
	char buf[BUFFSIZE];
	memset(buf, 0, sizeof(buf));
	int rc = recv(st, buf, sizeof(buf), 0);
    memset(LOGBUF,0,sizeof(LOGBUF));
    sprintf(LOGBUF,"[*] recv message:%s\n\n",buf);
    save_log(LOGBUF);
	if (rc <= 0)
	{
		memset(LOGBUF,0,sizeof(LOGBUF));
        sprintf(LOGBUF,"[-] %s,%d:recv failed %s\n", __FILE__, __LINE__,strerror(errno));
		save_log(LOGBUF);
	} else
	{
		char command[BUFFSIZE],uac[BUFFSIZE];
		memset(command, 0, sizeof(command));
		get_http_command(buf, command); 
        get_http_uac(buf, uac); 
        uac_parser(uac);
		char *content = NULL;
		int ilen = make_http_content(command, &content);
		if (ilen > 0)
		{
			send(st, content, ilen, 0); 
			memset(LOGBUF,0,sizeof(LOGBUF));
			sprintf(LOGBUF,"[+] send success %s\n",content);
			save_log(LOGBUF);
			free(content);
		}
	}
	close(st);
	return NULL;

}

pid_t Fork(void) 
{
    pid_t pid;

    if ((pid = fork()) < 0)
    {
        memset(LOGBUF,0,sizeof(LOGBUF));
        sprintf(LOGBUF,"[-] %s,%d:fork fail\n", __FILE__, __LINE__);
		save_log(LOGBUF);
	    exit(EXIT_FAILURE);
    }
    return pid;
}