 /******************************************************************************
*
*  Copyright (C), 2020-2025, haoside
*
*******************************************************************************
*  File Name     : main.c
*  Version       : Initial Draft
*  Author        : haoside
*  Created       : 2020/6/10
*  Last Modified :
*  Description   : main.c
*  Function List :
*
*       1.                gw_inuse_send
*       2.                main
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
#include "./gateway.h"
#include "./gw_tcp.h"
#include "./gw_http.h"
#include "./gw_udp.h"
/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/


/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/
void gw_inuse_send(void* pdata);

/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

/*****************************************************************************
*   Prototype    : main
*   Description  : Main Function
*   Input        : int argc      
*                  char *argv[]  
*   Output       : None
*   Return Value : int
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
int main(int argc , char *argv[])
{
    gw_management_pt iot_gw = gw_management_create();
    gw_init_tcp(iot_gw);
    gw_init_udp(iot_gw);
    gw_init_http(iot_gw);
    gw_management_cuid(iot_gw,(void *)gw_inuse_send);
    gw_management_delete(&iot_gw,1);
    gw_management_delete(&iot_gw,1);
    gw_management_delete(&iot_gw,1);
    gw_management_deleteList(&iot_gw);
    fflush(stdout);
    return 0;
}

/*****************************************************************************
*   Prototype    : gw_inuse_send
*   Description  : Find Inuse node In Gateway
*   Input        : gw_control_data_pt pdata  
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
void gw_inuse_send(void * pdata)
{
    int ret =0;
    gw_control_data_pt data=(gw_control_data_pt)pdata;
    if(data->flag==INUSE)
    {
        data->gw_init(pdata);
        ret = data->gw_sendfunction(data,"hello tanzhou\n");
        printf("Inuse type :%d Send Success\n",data->id);
    }
}
