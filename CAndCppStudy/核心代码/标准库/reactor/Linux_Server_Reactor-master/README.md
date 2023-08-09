# Linux Server Framework
## 主要模块 /communicate
C10K

这份代码框架包括（没有具体业务实现）

* reactor模式
* IO复用，统一信号源   IO通信模块 
	多线程accept 
	select  poll  
	epoll 
	
* 线程池，连接池    数据处理
* 消息队列。各个模块都是通过消息队列完成，异步插入
* 使用函数指针实现C的回调机制
* Linux下基本tcp通信

## 线程安全log系统 /spirit_log
* 线程锁
* pthread_key

## 连接池conn_pool
* 连接池及队列
* 使用回调方式




event_handler_t* ceh = create_package_operater(cli_fd, self->reactor);
   event_handler_t *acceptor = create_acceptor(listenfd,reactor);