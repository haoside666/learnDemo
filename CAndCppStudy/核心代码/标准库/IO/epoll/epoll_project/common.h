/******************************************************************************
*
*  Copyright (C), 2020-2025, haoside
*
*******************************************************************************
*  File Name     : common.h
*  Version       : Initial Draft
*  Author        : haoside
*  Created       : 2020/7/6
*  Last Modified :
*  Description   : common.c header file
*  Function List :
*
*
*  History:
* 
*       1.  Date         : 2020/7/6
*           Author       : haoside
*           Modification : Created file
*
******************************************************************************/
#ifndef __COMMON_H__
#define __COMMON_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*==============================================*
 *      include header files                    *
 *----------------------------------------------*/
#include <stdio.h>



/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/
#define SERVERIP "192.168.1.9"
#define SERVERPORT 7838
#define MAXBUF 8192
#define OPEN_MAX 1024
/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/
typedef struct package
{
    unsigned char dest_ip[16];
    unsigned short dest_port;
    char content[MAXBUF];
}package_t;
typedef struct package* package_pt;



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/

extern void packageTostr(char *buf,package_pt pkg);
extern void strTopackage(char *buf,package_pt pkg);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __COMMON_H__ */
