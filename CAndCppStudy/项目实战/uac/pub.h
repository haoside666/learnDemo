/******************************************************************************
*
*  Copyright (C), 2020-2025, haoside
*
*******************************************************************************
*  File Name     : pub.h
*  Version       : Initial Draft
*  Author        : haoside
*  Created       : 2020/9/6
*  Last Modified :
*  Description   : pub.c header file
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
#ifndef __PUB_H__
#define __PUB_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*==============================================*
 *      include header files                    *
 *----------------------------------------------*/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "thread_work.h"




/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/
#define BUFFSIZE 4096


/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/
char LOGBUF[BUFFSIZE];



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

extern const char *get_filetype(const char *filename);
extern int  get_file_content(const char *file_name, char **content);
extern void save_log(char *buf);
extern void setdaemon();
extern int socket_accept(int st);
extern int socket_create(int port);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __PUB_H__ */
