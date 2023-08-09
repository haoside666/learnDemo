/******************************************************************************
*
*  Copyright (C), 2020-2025, haoside
*
*******************************************************************************
*  File Name     : gw_udp.h
*  Version       : Initial Draft
*  Author        : haoside
*  Created       : 2020/6/10
*  Last Modified :
*  Description   : gw_udp.c header file
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
#ifndef __GW_UDP_H__
#define __GW_UDP_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*==============================================*
 *      include header files                    *
 *----------------------------------------------*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include "./gateway.h"

/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/
#define UDP_PORT 8081
#define UDP_SERVER "127.0.0.1"
/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

extern void gw_init_udp(gw_management_pt ptlist);
static int init_udp_gw_node(gw_control_data_pt pdata);
static void register_udp_proxy_method(gw_management_pt ptlist,void *pdata);
static int udp_gw_send(gw_control_data_pt pdata,void *sendbuffer);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __GW_UDP_H__ */
