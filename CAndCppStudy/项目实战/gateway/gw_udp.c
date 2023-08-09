

/******************************************************************************
*
*  Copyright (C), 2021-2025, haoside.
*
*******************************************************************************
*  File Name     : gw_udp.c
*  Version       : Initial Draft
*  Author        : haoside
*  Created       : 2021/10/12
*  Last Modified :
*  Description   : 12
*  Function List :
*
*       1.                gw_init_udp
*       2.                init_udp_gw_node
*       3.                register_udp_proxy_method
*       4.                udp_gw_send
*
*  History:
* 
*       1.  Date         : 2021/10/12
*           Author       : haoside
*           Modification : Created file
*
******************************************************************************/

/*==============================================*
 *      include header files                    *
 *----------------------------------------------*/




/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/


/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

/******************************************************************************
*
*  Copyright (C), 2020-2025, haoside
*
*******************************************************************************
*  File Name     : gw_udp.c
*  Version       : Initial Draft
*  Author        : haoside
*  Created       : 2020/6/10
*  Last Modified :
*  Description   : Gateway Udp node
*  Function List :
*
*       1.                gw_init_udp
*       2.                init_udp_gw_node
*       3.                register_udp_proxy_method
*       4.                udp_gw_send
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
#include "./gw_udp.h"

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
*   Prototype    : init_udp_gw_node
*   Description  : Inline Gateway udp node
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
static int init_udp_gw_node(gw_control_data_pt pdata)
{
    if((pdata->fd=socket(AF_INET,SOCK_DGRAM,0))<0)
    {
        perror("udp:socket create error\n");
    }
    return 1;
}

/*****************************************************************************
*   Prototype    : udp_gw_send
*   Description  : Gateway udp send
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
static int udp_gw_send(gw_control_data_pt pdata,void *sendbuffer)
{
    struct sockaddr_in seraddr;
    bzero(&seraddr,sizeof(seraddr));
    seraddr.sin_family =AF_INET;
    seraddr.sin_port = htons(UDP_PORT);
    if(inet_pton(AF_INET,UDP_SERVER,&seraddr.sin_addr)<=0)
        perror("udp:inet_pton error\n");
    
    int ret = sendto(pdata->fd,sendbuffer,strlen((char*)sendbuffer),0,(struct sockaddr*)&seraddr,sizeof(seraddr));
    if(ret<0)
        perror("udp write error\n");
    else
        printf("UDP Send Success,send length:%d\n",ret);
    return ret;
}

static gw_control_data_t gw_udp_node ={
    .id = UDP,
    .flag = INUSE,
    .gw_init =init_udp_gw_node,
    .gw_sendfunction=udp_gw_send,
};
/*****************************************************************************
*   Prototype    : register_udp_proxy_method
*   Description  : Gateway udp node register
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
static void register_udp_proxy_method(gw_management_pt ptlist,void *pdata)
{
    if(ptlist==NULL||pdata==NULL)
    {
        errno =EINVAL;
        return;
    }
    gw_management_insert_after(&ptlist,1,pdata);
}

/*****************************************************************************
*   Prototype    : gw_init_udp
*   Description  : Gateway udp node init
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
void gw_init_udp(gw_management_pt ptlist)
{
    register_udp_proxy_method(ptlist,(void *)&gw_udp_node);
}
