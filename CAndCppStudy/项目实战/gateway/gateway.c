/******************************************************************************
*
*  Copyright (C), 2020-2025, haoside
*
*******************************************************************************
*  File Name     : gateway.c
*  Version       : Initial Draft
*  Author        : haoside
*  Created       : 2020/6/10
*  Last Modified :
*  Description   : Home Gateway Core Level Code
*  Function List :
*
*       1.                gw_management_create
*       2.                gw_management_cuid
*       3.                gw_management_delete
*       4.                gw_management_insert_after
*       5.                gw_management_insert_before
*       6.                gw_management_modify
*       7.                gw_management_search
*       8.                gw_node_visit
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
*   Prototype    : gw_management_create
*   Description  : Gateway Core Management List Create
*   Input        : void  
*   Output       : None
*   Return Value : gw_management_pt
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
gw_management_pt gw_management_create(void)
{
    gw_management_pt list_head=NULL;
    list_head = (gw_management_pt)malloc(sizeof(gw_management_t));
    if(list_head==NULL)
    {
        errno = ENOMEM;
        exit(errno);
    }
    list_head->limit_size =0;
    list_head->head = (gw_control_node_pt)malloc(sizeof(gw_control_node_t));
    if(list_head->head==NULL)
    {
       errno = ENOMEM;
       exit(errno);
    }
    list_head->head->next = list_head->head->prev = NULL;
    list_head->head->data=NULL;
    list_head->tail = list_head->head;
    return list_head;
}

/*****************************************************************************
*   Prototype    : gw_management_insert_before
*   Description  : Gateway Register Func
*   Input        : gw_management_t **list_head  
*                  int num                      
*                  void *new_node_data          
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
int gw_management_insert_before(gw_management_t **list_head,int num,void *new_node_data)
{ 
    if(list_head==NULL||*list_head==NULL)
    {
        errno=EINVAL;
        exit(errno);
    }
    if((*list_head)->limit_size!=0)
    {
         if(num>0 && num<=(*list_head)->limit_size)
         {
            gw_control_node_pt new_node = (gw_control_node_pt)malloc(sizeof(gw_control_node_t));
            gw_control_node_pt current =(*list_head)->head;
             if(new_node==NULL)
             {
                errno = ENOMEM;
                exit(errno);
             }
             new_node->data=new_node_data;
             new_node->prev=new_node->next=NULL;
             if(num==1)
             {
                (*list_head)->head->prev=new_node;
                new_node->next=(*list_head)->head;
                (*list_head)->head=new_node;
                (*list_head)->limit_size++;
                return 0;
             }
             for(int counter=1;counter<num;counter++)
             {
                current = current->next;
             }
             new_node->next = current;
             new_node->prev=current->prev;
             current->prev->next = new_node;
             current->prev = new_node;             
             (*list_head)->limit_size++;
             return 0;
         }
         else
         {
             errno= EINVAL;
             exit(errno);
         }
    }
    else
    {
        if(num!=0)
        {
            errno=EINVAL;
            return -1;
        }
        (*list_head)->head->data=new_node_data;
        (*list_head)->limit_size++;
        return 0 ;
    }
}

/*****************************************************************************
*   Prototype    : gw_management_insert_after
*   Description  : Gateway Register Func
*   Input        : gw_management_t **list_head  
*                  int num                      
*                  void *new_node_data          
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
int gw_management_insert_after(gw_management_t **list_head,int num,void *new_node_data)
{ 
    if(list_head==NULL||*list_head==NULL)
    {
        errno=EINVAL;
        exit(errno);
    }
    if((*list_head)->limit_size!=0)
    {          
         if(num>0 && num<=(*list_head)->limit_size)
         {
             gw_control_node_pt new_node = (gw_control_node_pt)malloc(sizeof(gw_control_node_t));
             gw_control_node_pt current =(*list_head)->head;
             if(new_node==NULL)
             {
                errno = ENOMEM;
                exit(errno);
             }
             new_node->data=new_node_data;
             new_node->prev=new_node->next=NULL; 
             if(num==(*list_head)->limit_size)
             {
                (*list_head)->tail->next=new_node;
                new_node->prev=(*list_head)->tail;
                (*list_head)->tail=new_node;
                (*list_head)->limit_size++;
                return 0;
             }
            for(int counter=1;counter<num;counter++)
            {
                current = current->next;
            }
            new_node->prev=current;
            new_node->next=current->next;
            current->next->prev=new_node;
            current->next=new_node;
            (*list_head)->limit_size++;
            return 0;
         }
         else
         {
             errno= EINVAL;
             exit(errno);
         }
    }
    else
    {
        if(num!=0)
        {
            errno=EINVAL;
            exit(errno);
        }
        (*list_head)->head->data=new_node_data;
        (*list_head)->limit_size++;
        return 0 ;
    }
}

/*****************************************************************************
*   Prototype    : gw_management_delete
*   Description  : Gateway Management Delete
*   Input        : gw_management_t **list_head  
*                  int num                      
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
int gw_management_delete(gw_management_t **list_head,int num)
{    
    if(list_head==NULL||*list_head==NULL||(*list_head)->limit_size==0)
    {
        errno=EINVAL;
        exit(errno);
    }
    gw_control_node_pt tmp = NULL;
    gw_control_node_pt current = (*list_head)->head;  
    if(num==1)
    {
        tmp=(*list_head)->head;
        (*list_head)->head=(*list_head)->head->next;
        free(tmp);
        tmp=NULL;
        (*list_head)->limit_size--;
        return 0;
    }
    if((*list_head)->limit_size==num)
    {
        tmp=(*list_head)->tail;
        (*list_head)->tail=(*list_head)->tail->prev;
        free(tmp);
        tmp=NULL;
        (*list_head)->limit_size--;
        return 0;
    }
    for(int counter=1;counter<num;counter++)
    {
        current = current->next;
    }
    tmp=current;
    current->prev->next=current->next;
    current->next->prev=current->prev;
    free(tmp);
    tmp=NULL;
    (*list_head)->limit_size--;
    return 0 ;
}

/*****************************************************************************
*   Prototype    : gw_management_modify
*   Description  : Gateway Node Modify
*   Input        : gw_management_t **list_head  
*                  int num                      
*                  void *new_node_data          
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
int gw_management_modify(gw_management_t **list_head,int num,void *new_node_data)
{  
    if(list_head==NULL||*list_head==NULL||num<0||num>(*list_head)->limit_size)
    {
        errno=EINVAL;
        exit(errno);
    }
    gw_control_node_pt current = (*list_head)->head;
    for(int counter=1;counter<num;counter++)
    {
        current=current->next;
    }
    current->data = new_node_data;
    return 0;
}

/*****************************************************************************
*   Prototype    : gw_node_visit
*   Description  : Gateway Inline Function For List search
*   Input        : gw_management_t **list_head  
*                  int num(>0)                      
*   Output       : None
*   Return Value : static inline void *
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
static inline void *gw_node_visit(gw_management_t **list_head,int num)
{   
    if(list_head==NULL||*list_head==NULL||num<=0||num >(*list_head)->limit_size)
    {
        errno =EINVAL;
        exit(errno);
    }
    gw_control_node_pt current = (*list_head)->head;
    for(int counter=1;counter<num;counter++)
    {
        current=current->next;
    }
    return (void *)current->data;
}

/*****************************************************************************
*   Prototype    : gw_management_cuid
*   Description  : Gateway List search
*   Input        : gw_management_t *list_head  
*                  void(*do_function)(void *)  
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
void gw_management_cuid(gw_management_t *list_head,void(*do_function)(void *))
{
    if(list_head==NULL||list_head->limit_size<=0)
    {
        errno =EINVAL;
        exit(errno);
    }
    for(int i=1;i<=list_head->limit_size;i++)
    {
        (*do_function)(gw_node_visit(&list_head,i));
    }
}

/*****************************************************************************
*   Prototype    : gw_management_search
*   Description  : Gateway List Compare Search
*   Input        : gw_management_t ** list_head  
*                  void * find_data              
*                  int(* compare)(void *         
*                  void *)                       
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
int gw_management_search(gw_management_t ** list_head,void * find_data,int(* compare)(void *,void *))
{   
    if(list_head==NULL||*list_head==NULL)
    {
        errno =EINVAL;
        exit(errno);
    }
    int counter=1;
    gw_control_node_pt current = (*list_head)->head;
    while(current!=NULL&&compare(current->data,find_data)!=0)
    {
        current =current->next;
        counter++;
    }
    if(current==NULL)
        return 0;
    return counter;
}

/*****************************************************************************
*   Prototype    : gw_management_deleteList
*   Description  : Gateway List delete
*   Input        : gw_management_t ** list_head  
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
void gw_management_deleteList(gw_management_t ** list_head)
{
    if(list_head==NULL||*list_head==NULL)
    {
        errno =EINVAL;
        exit(errno);
    }
    if((*list_head)->limit_size==0)
    {
        if((*list_head)->head)
            free((*list_head)->head);
        free((*list_head));
    }else
    {
        gw_control_node_pt tmp;
        gw_control_node_pt current = (*list_head)->head;
        for(int i=0;i<(*list_head)->limit_size;i++)
        {
            tmp=current;
            free(tmp);
            current=current->next;
        }
        free((*list_head));
    }
}