/******************************************************************************
*
*  Copyright (C), 2020-2025, haoside
*
*******************************************************************************
*  File Name     : wrap.h
*  Version       : Initial Draft
*  Author        : haoside
*  Created       : 2020/6/28
*  Last Modified :
*  Description   : wrap.c header file
*  Function List :
*
*
*  History:
* 
*       1.  Date         : 2020/6/28
*           Author       : haoside
*           Modification : Created file
*
******************************************************************************/
#ifndef __WRAP_H__
#define __WRAP_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*==============================================*
 *      include header files                    *
 *----------------------------------------------*/
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>


/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/


/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

extern int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr);
extern void Bind(int fd, const struct sockaddr *sa, socklen_t salen);
extern void Close(int fd);
extern void Connect(int fd, const struct sockaddr *sa, socklen_t salen);
extern void Listen(int fd, int backlog);
static ssize_t my_read(int fd, char *ptr);
extern void perr_exit(const char *s);
extern ssize_t Read(int fd, void *ptr, size_t nbytes);
extern ssize_t Readline(int fd, void *vptr, size_t maxlen);
extern ssize_t Readn(int fd, void *vptr, size_t n);
extern int Socket(int family, int type, int protocol);
extern ssize_t Write(int fd, const void *ptr, size_t nbytes);
extern ssize_t Writen(int fd, const void *vptr, size_t n);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __WRAP_H__ */
