#你应该先运行recv.c 在运行send.c(root)
* sudo recv
* sudo send [dest_addr] [key] [localaddr] [localport]
* key为p4ssw0rd
##具体操作如下
1. send.c向recv.c发送一个ping包如果key正确,则send.c与recv.c相连接

2. 连接成功后send可以发送包
**包的格式为:消息类型 [消息队列类型 or 内容] [消息队列内容]**
>  消息类型 1代表为消息队列类型 2.代表为普通类型
* 如果消息类型为1:则后面接[消息队列类型] [消息队列内容]
	1. 代表bash操作   [内容]:     命令
	2. 代表文件上传   [内容]:     需要上传的文件[绝对路径或相对路径]
	3. 代表文件下载   [内容]:     需要下载的文件[绝对路径]
> example:1(空格)消息队列类型(空格)命令
> 1 1 ls or 1 1 pwd 
> 1 2 ../hello.txt
> 1 3 /home/zhangsan/Desktop/hello.txt

*  如果消息类型为2,则后面接[内容]
	1. 如果是quit则退出
	2. 反之则echo回来
> example:2(空格)内容
> 2 quit
> 2 hello
