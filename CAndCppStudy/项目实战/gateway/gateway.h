/******************************************************************************
*
*  Copyright (C), 2020-2025, haoside
*
*******************************************************************************
*  File Name     : gateway.h
*  Version       : Initial Draft
*  Author        : haoside
*  Created       : 2020/6/10
*  Last Modified :
*  Description   : gateway.c header file
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
#ifndef __GATEWAY_H__
#define __GATEWAY_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*==============================================*
 *      include header files                    *
 *----------------------------------------------*/
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>

/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/
#define HTTP 1
#define TCP  2
#define UDP  3
#define UART 4
            
#define INUSE 1
#define UNUSE 0 
/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef struct gw_control_data
{
    u8  id;
    u8  flag;
    int fd;
    u8 * send_buffer;
    int (* gw_init)(struct gw_control_data *data);
    int (* gw_sendfunction)(struct gw_control_data *data,void *sendbuffer);
}gw_control_data_t;
typedef gw_control_data_t * gw_control_data_pt;

typedef struct gw_control_node
{
    gw_control_data_pt       data;
    struct gw_control_node * prev;
    struct gw_control_node * next;
}gw_control_node_t;
typedef gw_control_node_t * gw_control_node_pt;

typedef struct gw_management
{
    u32 limit_size;
    gw_control_node_pt head;
    gw_control_node_pt tail;
}gw_management_t;
typedef gw_management_t* gw_management_pt;

extern int errno;
/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

extern gw_management_pt gw_management_create(void);
extern void gw_management_cuid(gw_management_t *list_head,void(*do_function)(void *));
extern int gw_management_delete(gw_management_t **list_head,int num);
extern int gw_management_insert_after(gw_management_t **list_head,int num,void *new_node_data);
extern int gw_management_insert_before(gw_management_t **list_head,int num,void *new_node_data);
extern int gw_management_modify(gw_management_t **list_head,int num,void *new_node_data);
extern int gw_management_search(gw_management_t ** list_head,void * find_data,int(* compare)(void *,void *));
extern void gw_management_deleteList(gw_management_t ** list_head);
static inline void *gw_node_visit(gw_management_t **list_head,int num);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __GATEWAY_H__ */
