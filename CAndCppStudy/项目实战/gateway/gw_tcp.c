/******************************************************************************
*
*  Copyright (C), 2020-2025, haoside
*
*******************************************************************************
*  File Name     : gw_tcp.c
*  Version       : Initial Draft
*  Author        : haoside
*  Created       : 2020/6/10
*  Last Modified :
*  Description   : Gateway Tcp node
*  Function List :
*
*       1.                gw_init_tcp
*       2.                init_tcp_gw_node
*       3.                register_tcp_proxy_method
*       4.                tcp_gw_send
*
*  History:
* 
*       1.  Date         : 2020/6/10
*           Author       : haoside
*           Modification : Created file
*
******************************************************************************/

/*==============================================*
 *      include header files                    *
 *----------------------------------------------*/
#include "./gw_tcp.h"

/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/


/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

/*****************************************************************************
*   Prototype    : init_tcp_gw_node
*   Description  : Inline Gateway tcp node
*   Input        : gw_control_data_pt pdata  
*   Output       : None
*   Return Value : static int
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/6/10
*           Author       : haoside
*           Modification : Created function
*
*****************************************************************************/
static int init_tcp_gw_node(gw_control_data_pt pdata)
{
    if((pdata->fd=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        perror("tcp:socket create error\n");
    }
    struct sockaddr_in seraddr;
    bzero(&seraddr,sizeof(seraddr));
    seraddr.sin_family =AF_INET;
    seraddr.sin_port = htons(TCP_PORT);
    if(inet_pton(AF_INET,TCP_SERVER,&seraddr.sin_addr)<=0)
        perror("tcp:inet_pton error\n");
    if(connect(pdata->fd,(struct sockaddr*)&seraddr,sizeof(seraddr))<0)
        perror("tcp:connect error\n");
}
/*****************************************************************************
*   Prototype    : tcp_gw_send
*   Description  : Gateway tcp send
*   Input        : gw_control_data_pt pdata  
*                  void *sendbuffer          
*   Output       : None
*   Return Value : static int
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/6/10
*           Author       : haoside
*           Modification : Created function
*
*****************************************************************************/
static int tcp_gw_send(gw_control_data_pt pdata,void *sendbuffer)
{
    int ret = write(pdata->fd,sendbuffer,strlen((char*)sendbuffer));
    if(ret<0)
        perror("tcp:write error\n");
    else
        printf("Send Success,send length:%d\n",ret);
    return ret;
}
static gw_control_data_t gw_tcp_node ={
    .id = TCP,
    .flag = INUSE,
    .gw_init =init_tcp_gw_node,
    .gw_sendfunction=tcp_gw_send,
};

/*****************************************************************************
*   Prototype    : register_tcp_proxy_method
*   Description  : Gateway tcp node register
*   Input        : gw_management_pt ptlist  
*                  void *pdata              
*   Output       : None
*   Return Value : static void
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/6/10
*           Author       : haoside
*           Modification : Created function
*
*****************************************************************************/
static void register_tcp_proxy_method(gw_management_pt ptlist,void *pdata)
{
    if(ptlist==NULL||pdata==NULL)
    {
        errno =EINVAL;
        return;
    }
    gw_management_insert_after(&ptlist,0,pdata);
}

/*****************************************************************************
*   Prototype    : gw_init_tcp
*   Description  : Gateway tcp node init
*   Input        : gw_management_pt ptlist  
*   Output       : None
*   Return Value : void
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2020/6/10
*           Author       : haoside
*           Modification : Created function
*
*****************************************************************************/
void gw_init_tcp(gw_management_pt ptlist)
{
    register_tcp_proxy_method(ptlist,(void *)&gw_tcp_node);
}
