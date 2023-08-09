/******************************************************************************
*
*  Copyright (C), 2020-2025, haoside
*
*******************************************************************************
*  File Name     : thread_work.h
*  Version       : Initial Draft
*  Author        : haoside
*  Created       : 2020/9/6
*  Last Modified :
*  Description   : thread_work.c header file
*  Function List :
*
*
*  History:
* 
*       1.  Date         : 2020/9/6
*           Author       : haoside
*           Modification : Created file
*
******************************************************************************/
#ifndef __THREAD_WORK_H__
#define __THREAD_WORK_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*==============================================*
 *      include header files                    *
 *----------------------------------------------*/

#include"pub.h"
    
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>


/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/
#define HEAD "HTTP/1.0 200 OK\n\
        Content-Type: %s\n\
        Transfer-Encoding: chunked\n\
        Connection: Keep-Alive\n\
        Accept-Ranges:bytes\n\
        Content-Length:%d\n\n"
        
#define TAIL "\n\n"


/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/
extern char LOGBUF[4096];
extern char ** environ;


/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

extern void get_http_command(char *http_msg, char *command);
extern void get_http_uac(char *http_msg, char *uac);
extern void uac_parser(const char* uac);

extern void *http_thread(void *argc);
extern int make_http_content(const char *command, char **content);
extern pid_t Fork(void);
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __THREAD_WORK_H__ */
