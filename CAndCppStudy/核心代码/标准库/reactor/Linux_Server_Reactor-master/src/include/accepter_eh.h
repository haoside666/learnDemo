/******************************************************************************
*
*  Copyright (C), 2020-2025, haoside
*
*******************************************************************************
*  File Name     : accepter_eh.h
*  Version       : Initial Draft
*  Author        : haoside
*  Created       : 2020/9/16
*  Last Modified :
*  Description   : accepter_eh.c header file
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
#ifndef __ACCEPTER_EH_H__
#define __ACCEPTER_EH_H__


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
#include <unistd.h>
#include <fcntl.h>
#include "reactor.h"
#include "server.h"
#include "header.h"


/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/


/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

extern event_handler_t* create_acceptor(int fd, reactor_t* r);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __ACCEPTER_EH_H__ */
