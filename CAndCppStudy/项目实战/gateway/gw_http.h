/******************************************************************************
*
*  Copyright (C), 2020-2025, haoside
*
*******************************************************************************
*  File Name     : gw_http.h
*  Version       : Initial Draft
*  Author        : haoside
*  Created       : 2020/6/10
*  Last Modified :
*  Description   : gw_http.c header file
*  Function List :
*
*
*  History:
* 
*       1.  Date         : 2020/6/10
*           Author       : haoside
*           Modification : Created file
*
******************************************************************************/
#ifndef __GW_HTTP_H__
#define __GW_HTTP_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*==============================================*
 *      include header files                    *
 *----------------------------------------------*/
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "./gateway.h"

/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/
#define HTTP_PORT 8082
#define HTTP_SERVER "127.0.0.1"
/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

extern void gw_init_http(gw_management_pt ptlist);
static int http_gw_send(gw_control_data_pt pdata,void *sendbuffer);
static int init_http_gw_node(gw_control_data_pt pdata);
static void register_http_proxy_method(gw_management_pt ptlist,void *pdata);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __GW_HTTP_H__ */
