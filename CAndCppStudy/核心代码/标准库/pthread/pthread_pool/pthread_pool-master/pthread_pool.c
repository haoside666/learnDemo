
#include"pthread_pool.h"


tp_thread_info* malloc_pthread(int pthread_num);
tp_thread_pool *creat_thread_pool(int min_num, int max_num);
int creat_thread(tp_thread_info* thread_info,tp_thread_pool *this);
int tp_init(tp_thread_pool *this);
int tp_add_job(tp_thread_pool *this, tp_work *worker, tp_work_arg *arg);
tp_thread_info *tp_add_thread(tp_thread_pool *this);
static void *tp_work_thread(void *pthread);
tp_thread_info* get_thread_by_pid(tp_thread_pool* pool,pthread_t pid);
void tp_destory(tp_thread_pool *this);
static void *tp_manage_thread(void *pthread);


tp_thread_info* malloc_pthread(int pthread_num){
		tp_thread_info* head,*cur,*pre;

		head = (tp_thread_info*)malloc(sizeof(tp_thread_info));
		//head->pre = NULL;
		pthread_num--;
		
		cur = head;
		pre = NULL;
		while(pthread_num){
				cur->pre = pre;
				cur->next = (tp_thread_info*)malloc(sizeof(tp_thread_info));
				pre = cur;
				cur = cur->next;
				pthread_num--;
		}
		cur->next = NULL;

		return head;
}

tp_thread_pool *creat_thread_pool(int min_num, int max_num){
	tp_thread_pool *this = NULL;

	this = (tp_thread_pool*)malloc(sizeof(tp_thread_pool));	
	if(NULL == this)
		return NULL;

	memset(this, 0, sizeof(tp_thread_pool));
	if(min_num < 3)
		min_num = 3;
	if(max_num > 200)
		max_num = 200;
	this->min_th_num = min_num;
	this->cur_th_num = this->min_th_num;
	this->max_th_num = max_num;
	this->idle_th_num = this->cur_th_num;
	pthread_mutex_init(&this->tp_lock, NULL);
	if(NULL != this->thread_info)
		free(this->thread_info);
	this->thread_info = malloc_pthread(this->cur_th_num);

	if(NULL == this->thread_info){
		free(this);
		return NULL;
	}
	tp_init(this);
	
	return this;
}

int creat_thread(tp_thread_info* thread_info,tp_thread_pool *this){
		int err;
		pthread_cond_init(&thread_info->thread_cond, NULL);
		pthread_mutex_init(&thread_info->thread_lock, NULL);
		
		err = pthread_create(&thread_info->thread_id, NULL, tp_work_thread, this);
		if(0 != err){
			printf("tp_init: creat work thread failed\n");
			return 0;
		}
		pthread_detach(thread_info->thread_id);
		thread_info->status = 2;
		return 1;
}

int tp_init(tp_thread_pool *this){
	int i;
	int err;
	pthread_t pid;
	tp_thread_info* thread_info;
	
	for(thread_info = this->thread_info;thread_info!=NULL;thread_info = thread_info->next){
		if(creat_thread(thread_info,this))
			printf("tp_init: creat work thread %lu\n", thread_info->thread_id);
		else{
            printf("tp_init: creat thread failed!\n");
			return 0;
		}
	}

	err = pthread_create(&this->manage_thread_id, NULL, tp_manage_thread, this);

	if(0 != err){
		printf("tp_init: creat manage thread failed\n");
		return 0;
	}
	else{
		printf("tp_init: creat manage thread %lu\n", this->manage_thread_id);
		return 1;
	}
}

void tp_destory(tp_thread_pool *this){
    		
	
}
	
int tp_add_job(tp_thread_pool *this, tp_work *worker, tp_work_arg *arg){
	int i;
	int tmpid;
	tp_thread_info* thread_info,*new_thread;

repeat:	
//	for(i = 0;i<3;i++){
		for(thread_info = this->thread_info;thread_info!=NULL;thread_info = thread_info->next){
			if(pthread_mutex_lock(&thread_info->thread_lock)==0){
				if(thread_info->status == 2){
					printf("thread idle, thread id is %lu\n", thread_info->thread_id);
					//�����߳�״̬
		  			thread_info->status = 1;
					this->idle_th_num--;
					pthread_mutex_unlock(&thread_info->thread_lock);
					
					thread_info->th_work = worker;
					thread_info->th_arg = arg;
					pthread_cond_signal(&thread_info->thread_cond);
            		return;
	    		}
        	pthread_mutex_unlock(&thread_info->thread_lock);
			}
		}//end of for
//	}

	pthread_mutex_lock(&this->tp_lock);
	new_thread = NULL;
   
	if( (new_thread = tp_add_thread(this))!= NULL){
		
		new_thread->th_work = worker;
		new_thread->th_arg = arg;
		pthread_cond_signal(&new_thread->thread_cond);
		pthread_mutex_unlock(&this->tp_lock);
        return ;
    }
	pthread_mutex_unlock(&this->tp_lock);
	goto repeat;
	return;	
}


tp_thread_info *tp_add_thread(tp_thread_pool *this){
	int err;
	tp_thread_info* new_thread;
	tp_thread_info *last;
	
	new_thread = NULL;
	if( this->max_th_num <= this->cur_th_num )
		return NULL;
	last = this->thread_info;
	while(last->next){
		last = last->next;
	}
	
	new_thread = (tp_thread_info *)malloc(sizeof(tp_thread_info));
	if(NULL == new_thread)
		return NULL;
	
    last->next = new_thread;
	new_thread->pre = last;

	pthread_cond_init(&new_thread->thread_cond, NULL);
	pthread_mutex_init(&new_thread->thread_lock, NULL);

	this->cur_th_num++;
	
	err = pthread_create(&new_thread->thread_id, NULL, tp_work_thread, this);
	if(0 != err){
		free(new_thread);
		return NULL;
	}
	pthread_detach(new_thread->thread_id);
	new_thread->status = 2;
	printf("tp_add_thread---------------: creat work thread %lu\n", new_thread->thread_id);
	this->idle_th_num++;
	return new_thread;
}

void destory_thread(tp_thread_info* thread){
	tp_thread_info* pre,*next;
	pthread_mutex_destroy(&thread->thread_lock);
	pthread_cond_destroy(&thread->thread_cond);
    if(thread->next == NULL){
        thread->pre->next = NULL;
    }
    else{
	    pre = thread->pre;
	    next = thread->next;
	    pre->next = next;
	    next->pre = pre;
    }
	free(thread);
	
}

static void *tp_work_thread(void *pthread){
	pthread_t pid;
	tp_thread_pool *this = (tp_thread_pool*)pthread;
	tp_thread_info* thread;

    pid = pthread_self();
	
	//get current thread's seq in the thread info struct array.
	thread = get_thread_by_pid(this, pid);
	if(NULL == thread)
		return;
	printf("entering working thread , thread id is %lu\n", pid);
	
	while(1){
		pthread_mutex_lock(&thread->thread_lock);
       while(thread->status != 1){
		    pthread_cond_wait(&thread->thread_cond, &thread->thread_lock);
            if(thread->need_exit == 1)
                break;
       }
		if(thread->need_exit){
            printf("pthread %lu  will exit.....\n",pid);
			pthread_mutex_unlock(&thread->thread_lock);
			destory_thread(thread);
			this->cur_th_num--;
			this->idle_th_num--;
			return;
		}
		pthread_mutex_unlock(&thread->thread_lock);
		
		printf("%lu thread do work!\n", pid);
		tp_work *work = thread->th_work;
		tp_work_arg *arg = thread->th_arg;


		work->process_job(arg);

		free(arg);
		pthread_mutex_lock(&thread->thread_lock);		
		thread->status = 2;
		this->idle_th_num++;
		pthread_mutex_unlock(&thread->thread_lock);
		
		printf("%lu do work over\n", pid);
	}	
}

tp_thread_info* get_thread_by_pid(tp_thread_pool* pool,pthread_t pid){
	tp_thread_info* cur;
	cur = pool->thread_info;
	while(cur){
		if(pthread_equal(cur->thread_id,pid)){
				return cur;
		}
		cur = cur->next;
    }
	return NULL;
}

void *tp_manage_thread(void *pool_this){
	int cur,idle;
	int idle_arv[3] = {0};
	int average;
	int exit_num;
	int min;
    tp_thread_info*thread_info;

    tp_thread_pool *this = (tp_thread_pool*)pool_this;
	while(1){
		cur = this->cur_th_num;
		idle = this->idle_th_num;
		min = this->min_th_num;
		exit_num = 0;
		idle_arv[2] = idle;
		
		average = (idle_arv[0]+idle_arv[1]+idle_arv[2])/3;
	    printf("*****************************************\n");	
		printf("������ǰ����״̬��\n");
		printf("���߳�����%d\n",cur);
		printf("��ǰ�����߳�����%d\n",idle);
		printf("�߳�ƽ����������%d\n",average);
		if(average>(cur/2)){
				exit_num = cur/5;
		}
		if(cur-exit_num<min){
				exit_num = cur-min;
		}
        printf("��Ҫ���� %d ���߳�\n",exit_num);    
        printf("*****************************************\n");
	    for(thread_info = this->thread_info->next;thread_info!=NULL&&exit_num>0;thread_info = thread_info->next){
            pthread_mutex_lock(&thread_info->thread_lock);
			if(thread_info->status != 2){
                pthread_mutex_unlock(&thread_info->thread_lock);
				continue;
			}
			thread_info->need_exit = 1;
            pthread_mutex_unlock(&thread_info->thread_lock);
			exit_num--;
			pthread_cond_signal(&thread_info->thread_cond);
		}
		idle_arv[0] = idle_arv[1];
		idle_arv[1] = idle_arv[2];
		sleep(5);
	}
}
	
