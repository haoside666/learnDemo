

 /********************************** 
 * @author      wallwind@yeah.net
 * @date        2012/06/13
 * Last update: 2012/06/13
 * License:     LGPL
 * 
 **********************************/
 
 
 
 #ifndef _THPOOL_
 #define _THPOOL_
 
 // #include "global.h"
#include <semaphore.h>
#include <stdio.h>
 /**
	����һ������ڵ�
 **/
 typedef void* (*FUNC)(void* arg);
 
 
 typedef struct _thpool_job_t{
//	void* (*function)(void* arg);    //����ָ��
	FUNC 			 function;
	void*                   arg;     //����������
	struct _thpool_job_t* prev;     // ָ����һ���ڵ�
	struct _thpool_job_t* next;	    //ָ����һ���ڵ�
 } thpool_job_t;
 
 /**
	����һ�������
 **/
 
typedef struct _thpool_job_queue{
	thpool_job_t*    head;            //����ͷָ�� 
	thpool_job_t*    tail;			   // ����ĩβָ��
	int              jobN;					  //������
	sem_t*           queueSem;			  //x�ź���
}thpool_jobqueue; 
 
 /**
	�̳߳�
 **/
 typedef struct _thpool_t{
	pthread_t*      threads;    ////�߳�ָ����
	int 		    threadsN;    //// �߳���
	thpool_jobqueue* jobqueue;   // ָ�����ָ��
 }thpool_t;

 
 typedef struct thread_data{                            
	pthread_mutex_t *mutex_p;
	thpool_t        *tp_p;
}thread_data;


 //��ʼ���̳߳��ڲ����߳���
thpool_t*  thpool_init(int threadN);

void thpool_thread_do(thpool_t* tp_p);

int thpool_add_work(thpool_t* tp_p, void *(*function_p)(void*), void* arg_p);

void thpool_destroy(thpool_t* tp_p);



int thpool_jobqueue_init(thpool_t* tp_p);



void thpool_jobqueue_add(thpool_t* tp_p, thpool_job_t* newjob_p);

int thpool_jobqueue_removelast(thpool_t* tp_p);

thpool_job_t* thpool_jobqueue_peek(thpool_t* tp_p);

void thpool_jobqueue_empty(thpool_t* tp_p);

 #endif



