/******************************************************************************
*
*  Copyright (C), 2020-2025, haoside
*
*******************************************************************************
*  File Name     : gw_tcp.h
*  Version       : Initial Draft
*  Author        : haoside
*  Created       : 2020/6/10
*  Last Modified :
*  Description   : gw_tcp.c header file
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
#ifndef __GW_TCP_H__
#define __GW_TCP_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*==============================================*
 *      include header files                    *
 *----------------------------------------------*/
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include "./gateway.h"

/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/
#define TCP_PORT 8080
#define TCP_SERVER "127.0.0.1"
/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

extern void gw_init_tcp(gw_management_pt ptlist);
static int init_tcp_gw_node(gw_control_data_pt pdata);
static void register_tcp_proxy_method(gw_management_pt ptlist,void *pdata);
static int tcp_gw_send(gw_control_data_pt pdata,void *sendbuffer);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __GW_TCP_H__ */
