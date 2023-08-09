https://blog.csdn.net/hwx865/article/details/90287715

```
安装MySQL服务器
sudo apt install mysql-server

安装MySQL服务器
sudo apt-get install mysql-client
```



```
设置密码
sudo mysql
show variables like 'validate_password%';
set global validate_password.length=6;

alter  user  'root'@'localhost'  identified  with  mysql_native_password  by  '密码';

运行MySQL初始化安全脚本
sudo mysql_secure_installation
	mysql_secure_installation脚本设置的东西：更改root密码、移除MySQL的匿名用户、禁止root远程登录、删除test数据库和重新加载权限。


创建新用户用于在任意平台登录，并且能操作所有的数据库及所有的表：
create  user  'haoside'@'%' identified  with  mysql_native_password  by '密码';
grant all privileges  on  *.* to 'haoside'@'%';
mysql -u haoside -p


```

## 配置MySQL远程登录

```
MySQL的配置文件
sudo vim /etc/mysql/mysql.conf.d/mysqld.cnf

有时候，为了开发方便，我们需要使用本地电脑远程访问和管理MySQL数据库。默认情况下，为了安全MySQL只允许本地登录，如果要开启远程连接，则需要修改/etc/mysql/mysql.conf.d/mysqld.cnf配置文件。

打开配置文件，找到bind-address = 127.0.0.1这一行
改为bind-address = 0.0.0.0即可或简单一点注释掉也行

修改完成保存后，需要重启MySQL服务才会生效

接着需要为用户赋予远程登录的权限，使用以下用户授权步骤即可
```

## 设置MySQL服务

```
设置MySQL服务
sudo systemctl restart/stop/start/status  mysql.service
设置MySQL服务开机自启动
sudo systemctl enable mysql.service
停止MySQL服务开机自启动
sudo systemctl disable mysql.service
```

## 物理机安装navicat连接虚拟机mysql

```
略
```



