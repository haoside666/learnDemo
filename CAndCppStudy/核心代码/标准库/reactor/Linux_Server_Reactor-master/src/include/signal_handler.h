/******************************************************************************
*
*  Copyright (C), 2020-2025, haoside
*
*******************************************************************************
*  File Name     : signal_handler.h
*  Version       : Initial Draft
*  Author        : haoside
*  Created       : 2020/9/16
*  Last Modified :
*  Description   : signal_handler.c header file
*  Function List :
*
*
*  History:
* 
*       1.  Date         : 2020/9/16
*           Author       : haoside
*           Modification : Created file
*
******************************************************************************/
#ifndef __SIGNAL_HANDLER_H__
#define __SIGNAL_HANDLER_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*==============================================*
 *      include header files                    *
 *----------------------------------------------*/
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h> //malloc
#include <sys/epoll.h>
#include <errno.h>
#include <signal.h>
#include <assert.h>
#include <unistd.h>
#include "reactor.h"
#include "server.h"
#include "header.h"




/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/


/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/
static int pipefd[2];



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

extern event_handler_t* create_signal_accepter(reactor_t* r,int sig);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __SIGNAL_HANDLER_H__ */
