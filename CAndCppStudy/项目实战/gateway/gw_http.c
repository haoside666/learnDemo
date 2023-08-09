
/******************************************************************************
*
*  Copyright (C), 2020-2025, haoside
*
*******************************************************************************
*  File Name     : gw_http.c
*  Version       : Initial Draft
*  Author        : haoside
*  Created       : 2020/6/10
*  Last Modified :
*  Description   : Gateway Http node
*  Function List :
*
*       1.                gw_init_http
*       2.                http_gw_send
*       3.                init_http_gw_node
*       4.                register_http_proxy_method
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
#include "./gw_http.h"

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
*   Prototype    : init_http_gw_node
*   Description  : Inline Gateway http node
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
static int init_http_gw_node(gw_control_data_pt pdata)
{
    if((pdata->fd=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        perror("http:socket create error\n");
    }
    struct sockaddr_in seraddr;
    bzero(&seraddr,sizeof(seraddr));
    seraddr.sin_family =AF_INET;
    seraddr.sin_port = htons(HTTP_PORT);
    if(inet_pton(AF_INET,HTTP_SERVER,&seraddr.sin_addr)<=0)
        perror("http:inet_pton error\n");
    if(connect(pdata->fd,(struct sockaddr*)&seraddr,sizeof(seraddr))<0)
        perror("http:connect error\n");
}

/*****************************************************************************
*   Prototype    : http_gw_send
*   Description  : Gateway http send
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
static int http_gw_send(gw_control_data_pt pdata,void *sendbuffer)
{
    u8 *length=(u8 *)malloc(128);
    int len = strlen(sendbuffer);
    sprintf(length,"%d",len);
    u8 *http_data =(u8 *)malloc(len+1024);
    memset(http_data , 0, len+1024);
    strcat(http_data, "POST /webservices/qqOnlineWebService.asmx/qqCheckOnline HTTP/1.1\r\n");
    strcat(http_data, "Host: www.webxml.com.cn\r\n");
    strcat(http_data, "Content-Type: application/x-www-form-urlencoded\r\n");
    strcat(http_data, "Content-Length: ");
    strcat(http_data, length);
    strcat(http_data, "\r\n");
    strcat(http_data, sendbuffer);
    strcat(http_data, "\r\n\r\n");

    int ret = write(pdata->fd,http_data,strlen(http_data));
    if(ret<0)
        perror("http:write error\n");
    else
        printf("HTTP Send Success,send length:%d\n",ret);
    free(length);
    free(http_data);
    length=NULL;
    http_data=NULL;
    return ret;
}

static gw_control_data_t gw_http_node ={
    .id = HTTP,
    .flag = INUSE,
    .gw_init =init_http_gw_node,
    .gw_sendfunction=http_gw_send,
};

/*****************************************************************************
*   Prototype    : register_http_proxy_method
*   Description  : Gateway http node register
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
static void register_http_proxy_method(gw_management_pt ptlist,void *pdata)
{
    if(ptlist==NULL||pdata==NULL)
    {
        errno =EINVAL;
        return;
    }
    gw_management_insert_after(&ptlist,1,pdata);
}

/*****************************************************************************
*   Prototype    : gw_init_http
*   Description  : Gateway http node init
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
void gw_init_http(gw_management_pt ptlist)
{
    register_http_proxy_method(ptlist,(void *)&gw_http_node);
}
