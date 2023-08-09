# 事务和锁

# 一、事务
-- 1、事务的概念
# DBMS(数据库管理系统)把创建数据库、创建数据表以及对表的插入、更新、删除或者执行存储过程。。。都当作一个事务进行处理
# 事务是作为单个逻辑单元所执行的一系列操作。

-- 2、事务的特性
# 事务由ACID四个基本要素
-- A：Atomicity，事务要具有原子性。
-- C：consistency，一致性
-- I：lsolatiom，隔离性，不同的事务是不相互干扰的
-- D：Durablily，持久性，事务一旦成功提交，数据就不会因为其他的原因而改变

-- 3、事务控制
# 事务的控制有两种方法：
-- ①隐式事务
# 单独的某些事务（如：创建数据库、创建数据表以及对表的插入、更新、删除或者执行存储过程）默认是隐式事务，由系统自动提交
create database tzdb3;

use tzdb1;

-- ②显式事务
# 显示事务不是由系统自动提交，是需要手动提交。

-- 4、隐式事务
delete from student where s_id = 6;

select * from student;

# ①查看自动提交的状态
show variables like "autocommit";
-- 隐式事务自动提交是由一个autocommit变量来控制的。

# ②关闭自动提交
# 通过设置自动提交变量的值为off或者0来关闭自动提交
set autocommit = off;

delete from student where s_id = 9;

-- 5、回滚
/* 
没有设置自动提交，数据并没有从数据表中真实的修改，只是在临时结果集中修改了。
*/
# 回滚关键字：rollback
rollback;
# 可以通过回滚撤销操作
select * from student;

-- 6、提交（确认事务）

# 提交事务关键字：commmit
delete from student where s_id = 9;
# 确认提交
commit;
# 确认提交后回滚就没用了
rollback;

set autocommit = 1;

-- 7、显示事务
# 事务的显示控制
-- 事务显示控制基本格式：start transaction; (开始显示事务)
start transaction;
delete from student where s_id = 5;

select * from student;

rollback;

start transaction;

delete from student where s_id = 4;

commit;

-- 8、事务的隔离
# 数据库的使用过程中，无法避免的会有多个用户同时操作一个数据表的情况，操作可能会起冲突
# 所以就产生了事务的并发控制的概念，也就是使每个用户的事务要隔离开来。

# ①事务的隔离级别（从低到高）
-- 读未提交：就是一个用户执行一个事务但没提交，另一个用户可以读到没提交的数据。
	# 读未提交会导致“脏读”问题
-- 读提交：就是一个用户执行一个事务但没提交，另一个用户不可以读到没提交的数据。
	# 虽然读提交解决了“脏读”问题，但是会产生一个“不可重读”问题
-- 可重读(MySQL默认)：解决不可重读问题
	# 会出现新的“幻读”问题
-- 串行化读：不允许并发，也就是不允许多个用户同时操作同一个表。
	/*只有等上一个用户操作完成了之后，下一个用户才能够操作，
    牺牲了用户的时间，需要等待，来保证数据的准确性和一致性
    */

-- 9、事务隔离的验证
# ①创建一个事务隔离的测试表
use tzdb3;

create table test
(
id int primary key auto_increment,
name varchar(20),
age int
)engine innodb default charset utf8;

insert into test values(null,'号卫',18),(null,'梦幻星辰',19),(null,'诚信的筹码',20);

select * from test;

# ②查看当前隔离级别
-- 保存隔离级别的变量有两种：全局变量，会话变量
# 查看会话级别的隔离：
select @@session.tx_isolation;
-- 当前连接有效
# MySQL默认为 REPEATABLE-READ（可重读）repeatable-read

# 查看全局级别的隔离：
-- 当前服务有效
select @@global.tx_isolation;

-- 10、设置当前的隔离级别
# 会话级：
set session transaction isolation level read uncommitted; #设置当前会话隔离级别为读未提交

set session transaction isolation level read committed; #设置当前会话隔离级别为读提交

set session transaction isolation level repeatable read; #设置当前会话隔离级别为可重读

set session transaction isolation level serializable; #设置当前会话隔离级别为串行化读

# 全局级：
set global transaction isolation level read uncommitted; #设置当前全局隔离级别为读未提交

set global transaction isolation level read committed; #设置当前全局隔离级别为读提交

set global transaction isolation level repeatable read; #设置当前全局隔离级别为可重读

set global transaction isolation level serializable; #设置当前全局隔离级别为串行化读

# 测试隔离级别
-- 用会话级别的隔离进行测试
/*用户A:
mysql> use tzdb3;
Database changed
mysql> select @@session.tx_isolation;
+------------------------+
| @@session.tx_isolation |
+------------------------+
| REPEATABLE-READ        |
+------------------------+
1 row in set, 1 warning (0.00 sec)

mysql> set session transaction isolation level read uncommitted;
Query OK, 0 rows affected (0.00 sec)

mysql> select @@session.tx_isolation;
+------------------------+
| @@session.tx_isolation |
+------------------------+
| READ-UNCOMMITTED       |
+------------------------+
1 row in set, 1 warning (0.00 sec)

mysql> start transaction;
Query OK, 0 rows affected (0.00 sec)

mysql> update test set age=16 where id =1;
Query OK, 1 row affected (0.01 sec)
Rows matched: 1  Changed: 1  Warnings: 0

mysql> select * from test;
+----+-----------------+------+
| id | name            | age  |
+----+-----------------+------+
|  1 | 号卫            |   16 |
|  2 | 梦幻星辰        |   19 |
|  3 | 诚信的筹码      |   20 |
+----+-----------------+------+
3 rows in set (0.00 sec)

mysql> rollback;
Query OK, 0 rows affected (0.00 sec)

mysql> select * from test;
+----+-----------------+------+
| id | name            | age  |
+----+-----------------+------+
|  1 | 号卫            |   18 |
|  2 | 梦幻星辰        |   19 |
|  3 | 诚信的筹码      |   20 |
+----+-----------------+------+
3 rows in set (0.00 sec)

mysql> select @@session.tx_isolation;
+------------------------+
| @@session.tx_isolation |
+------------------------+
| READ-UNCOMMITTED       |
+------------------------+
1 row in set, 1 warning (0.00 sec)

mysql> set session transaction isolation level read committed;
Query OK, 0 rows affected (0.00 sec)

mysql> select @@session.tx_isolation;
+------------------------+
| @@session.tx_isolation |
+------------------------+
| READ-COMMITTED         |
+------------------------+
1 row in set, 1 warning (0.00 sec)

mysql> start transaction;
Query OK, 0 rows affected (0.00 sec)

mysql> update test set age=16 where id =1;
Query OK, 1 row affected (0.00 sec)
Rows matched: 1  Changed: 1  Warnings: 0

mysql> select * from test;
+----+-----------------+------+
| id | name            | age  |
+----+-----------------+------+
|  1 | 号卫            |   16 |
|  2 | 梦幻星辰        |   19 |
|  3 | 诚信的筹码      |   20 |
+----+-----------------+------+
3 rows in set (0.00 sec)

mysql> commit;
Query OK, 0 rows affected (0.01 sec)

mysql> select * from test;
+----+-----------------+------+
| id | name            | age  |
+----+-----------------+------+
|  1 | 号卫            |   16 |
|  2 | 梦幻星辰        |   19 |
|  3 | 诚信的筹码      |   20 |
+----+-----------------+------+
3 rows in set (0.00 sec)

mysql> select @@session.tx_isolation;
+------------------------+
| @@session.tx_isolation |
+------------------------+
| READ-COMMITTED         |
+------------------------+
1 row in set, 1 warning (0.00 sec)

mysql> set session transaction isolation level repeatable read;
Query OK, 0 rows affected (0.00 sec)

mysql> select @@session.tx_isolation;
+------------------------+
| @@session.tx_isolation |
+------------------------+
| REPEATABLE-READ        |
+------------------------+
1 row in set, 1 warning (0.00 sec)

mysql> start transaction;
Query OK, 0 rows affected (0.00 sec)

mysql> select * from test;
+----+-----------------+------+
| id | name            | age  |
+----+-----------------+------+
|  1 | 号卫            |   16 |
|  2 | 梦幻星辰        |   19 |
|  3 | 诚信的筹码      |   20 |
+----+-----------------+------+
3 rows in set (0.00 sec)

mysql> select * from test;
+----+-----------------+------+
| id | name            | age  |
+----+-----------------+------+
|  1 | 号卫            |   16 |
|  2 | 梦幻星辰        |   19 |
|  3 | 诚信的筹码      |   20 |
+----+-----------------+------+
3 rows in set (0.00 sec)

mysql> select * from test;
+----+-----------------+------+
| id | name            | age  |
+----+-----------------+------+
|  1 | 号卫            |   16 |
|  2 | 梦幻星辰        |   19 |
|  3 | 诚信的筹码      |   20 |
+----+-----------------+------+
3 rows in set (0.00 sec)

mysql> select * from test;
+----+-----------------+------+
| id | name            | age  |
+----+-----------------+------+
|  1 | 号卫            |   16 |
|  2 | 梦幻星辰        |   19 |
|  3 | 诚信的筹码      |   20 |
+----+-----------------+------+
3 rows in set (0.00 sec)

mysql> select * from test;
+----+-----------------+------+
| id | name            | age  |
+----+-----------------+------+
|  1 | 号卫            |   16 |
|  2 | 梦幻星辰        |   19 |
|  3 | 诚信的筹码      |   20 |
+----+-----------------+------+
3 rows in set (0.00 sec)

mysql> commit;
Query OK, 0 rows affected (0.00 sec)

mysql> select * from test;
+----+-----------------+------+
| id | name            | age  |
+----+-----------------+------+
|  1 | 号卫            |   22 |
|  2 | 梦幻星辰        |   19 |
|  3 | 诚信的筹码      |   20 |
+----+-----------------+------+
3 rows in set (0.00 sec)

mysql> select @@session.tx_isolation;
+------------------------+
| @@session.tx_isolation |
+------------------------+
| REPEATABLE-READ        |
+------------------------+
1 row in set, 1 warning (0.00 sec)

mysql> set session transaction isolation level serializable;
Query OK, 0 rows affected (0.00 sec)

mysql> select @@session.tx_isolation;
+------------------------+
| @@session.tx_isolation |
+------------------------+
| SERIALIZABLE           |
+------------------------+
1 row in set, 1 warning (0.00 sec)

mysql> select * from test;
+----+-----------------+------+
| id | name            | age  |
+----+-----------------+------+
|  1 | 号卫            |   22 |
|  2 | 梦幻星辰        |   19 |
|  3 | 诚信的筹码      |   20 |
+----+-----------------+------+
3 rows in set (0.00 sec)

mysql> start transaction;
Query OK, 0 rows affected (0.00 sec)

mysql> select * from test;
+----+-----------------+------+
| id | name            | age  |
+----+-----------------+------+
|  1 | 号卫            |   24 |
|  2 | 梦幻星辰        |   19 |
|  3 | 诚信的筹码      |   20 |
+----+-----------------+------+
3 rows in set (21.30 sec)

mysql> commit;
Query OK, 0 rows affected (0.00 sec)
*/

/*用户B
mysql> use tzdb3;
Database changed
mysql> select @@session.tx_isolation;
+------------------------+
| @@session.tx_isolation |
+------------------------+
| REPEATABLE-READ        |
+------------------------+
1 row in set, 1 warning (0.00 sec)

mysql> set session transaction isolation level read uncommitted;
Query OK, 0 rows affected (0.00 sec)

mysql> select @@session.tx_isolation;
+------------------------+
| @@session.tx_isolation |
+------------------------+
| READ-UNCOMMITTED       |
+------------------------+
1 row in set, 1 warning (0.00 sec)

mysql> select * from test;
+----+-----------------+------+
| id | name            | age  |
+----+-----------------+------+
|  1 | 号卫            |   18 |
|  2 | 梦幻星辰        |   19 |
|  3 | 诚信的筹码      |   20 |
+----+-----------------+------+
3 rows in set (0.01 sec)

mysql> select * from test;
+----+-----------------+------+
| id | name            | age  |
+----+-----------------+------+
|  1 | 号卫            |   16 |
|  2 | 梦幻星辰        |   19 |
|  3 | 诚信的筹码      |   20 |
+----+-----------------+------+
3 rows in set (0.00 sec)

mysql> select * from test;
+----+-----------------+------+
| id | name            | age  |
+----+-----------------+------+
|  1 | 号卫            |   16 |
|  2 | 梦幻星辰        |   19 |
|  3 | 诚信的筹码      |   20 |
+----+-----------------+------+
3 rows in set (0.00 sec)

mysql> select * from test;
+----+-----------------+------+
| id | name            | age  |
+----+-----------------+------+
|  1 | 号卫            |   18 |
|  2 | 梦幻星辰        |   19 |
|  3 | 诚信的筹码      |   20 |
+----+-----------------+------+
3 rows in set (0.00 sec)

mysql> select @@session.tx_isolation;
+------------------------+
| @@session.tx_isolation |
+------------------------+
| READ-UNCOMMITTED       |
+------------------------+
1 row in set, 1 warning (0.00 sec)

mysql> set session transaction isolation level read committed;
Query OK, 0 rows affected (0.00 sec)

mysql> select @@session.tx_isolation;
+------------------------+
| @@session.tx_isolation |
+------------------------+
| READ-COMMITTED         |
+------------------------+
1 row in set, 1 warning (0.00 sec)

mysql> select * from test;
+----+-----------------+------+
| id | name            | age  |
+----+-----------------+------+
|  1 | 号卫            |   18 |
|  2 | 梦幻星辰        |   19 |
|  3 | 诚信的筹码      |   20 |
+----+-----------------+------+
3 rows in set (0.00 sec)

mysql> select * from test;
+----+-----------------+------+
| id | name            | age  |
+----+-----------------+------+
|  1 | 号卫            |   18 |
|  2 | 梦幻星辰        |   19 |
|  3 | 诚信的筹码      |   20 |
+----+-----------------+------+
3 rows in set (0.00 sec)

mysql> select * from test;
+----+-----------------+------+
| id | name            | age  |
+----+-----------------+------+
|  1 | 号卫            |   16 |
|  2 | 梦幻星辰        |   19 |
|  3 | 诚信的筹码      |   20 |
+----+-----------------+------+
3 rows in set (0.00 sec)

mysql> select @@session.tx_isolation;
+------------------------+
| @@session.tx_isolation |
+------------------------+
| READ-COMMITTED         |
+------------------------+
1 row in set, 1 warning (0.00 sec)

mysql> select @@session.tx_isolation;
+------------------------+
| @@session.tx_isolation |
+------------------------+
| READ-COMMITTED         |
+------------------------+
1 row in set, 1 warning (0.00 sec)

mysql> set session transaction isolation level repeatable read;
Query OK, 0 rows affected (0.00 sec)

mysql> select @@session.tx_isolation;
+------------------------+
| @@session.tx_isolation |
+------------------------+
| REPEATABLE-READ        |
+------------------------+
1 row in set, 1 warning (0.00 sec)

mysql> start transaction;
Query OK, 0 rows affected (0.00 sec)

mysql> updata test set age = 22 where id =1;
ERROR 1064 (42000): You have an error in your SQL syntax; check the manual that corresponds to your MySQL server version for the right syntax to use near 'updata test set age = 22 where id =1' at line 1
mysql> update test set age = 22 where id =1;
Query OK, 1 row affected (0.00 sec)
Rows matched: 1  Changed: 1  Warnings: 0

mysql> select * from test;
+----+-----------------+------+
| id | name            | age  |
+----+-----------------+------+
|  1 | 号卫            |   22 |
|  2 | 梦幻星辰        |   19 |
|  3 | 诚信的筹码      |   20 |
+----+-----------------+------+
3 rows in set (0.00 sec)

mysql> commit;
Query OK, 0 rows affected (0.01 sec)

mysql> select * from test;
+----+-----------------+------+
| id | name            | age  |
+----+-----------------+------+
|  1 | 号卫            |   22 |
|  2 | 梦幻星辰        |   19 |
|  3 | 诚信的筹码      |   20 |
+----+-----------------+------+
3 rows in set (0.00 sec)

mysql> select * from test;
+----+-----------------+------+
| id | name            | age  |
+----+-----------------+------+
|  1 | 号卫            |   22 |
|  2 | 梦幻星辰        |   19 |
|  3 | 诚信的筹码      |   20 |
+----+-----------------+------+
3 rows in set (0.00 sec)

mysql> select @@session.tx_isolation;
+------------------------+
| @@session.tx_isolation |
+------------------------+
| REPEATABLE-READ        |
+------------------------+
1 row in set, 1 warning (0.00 sec)

mysql> set session transaction isolation level serializable;
Query OK, 0 rows affected (0.00 sec)

mysql> select @@session.tx_isolation;
+------------------------+
| @@session.tx_isolation |
+------------------------+
| SERIALIZABLE           |
+------------------------+
1 row in set, 1 warning (0.00 sec)

mysql> start transaction;
Query OK, 0 rows affected (0.00 sec)

mysql> updata test set age = 24 where id =1;
ERROR 1064 (42000): You have an error in your SQL syntax; check the manual that corresponds to your MySQL server version for the right syntax to use near 'updata test set age = 24 where id =1' at line 1
mysql> update test set age = 24 where id =1;
Query OK, 1 row affected (0.00 sec)
Rows matched: 1  Changed: 1  Warnings: 0

mysql> select * from test;
+----+-----------------+------+
| id | name            | age  |
+----+-----------------+------+
|  1 | 号卫            |   24 |
|  2 | 梦幻星辰        |   19 |
|  3 | 诚信的筹码      |   20 |
+----+-----------------+------+
3 rows in set (0.00 sec)

mysql> commit;
Query OK, 0 rows affected (0.01 sec)

mysql> select * from test;
+----+-----------------+------+
| id | name            | age  |
+----+-----------------+------+
|  1 | 号卫            |   24 |
|  2 | 梦幻星辰        |   19 |
|  3 | 诚信的筹码      |   20 |
+----+-----------------+------+
3 rows in set (0.00 sec)

mysql> start transaction;
Query OK, 0 rows affected (0.00 sec)

mysql> select * from test;
+----+-----------------+------+
| id | name            | age  |
+----+-----------------+------+
|  1 | 号卫            |   24 |
|  2 | 梦幻星辰        |   19 |
|  3 | 诚信的筹码      |   20 |
+----+-----------------+------+
3 rows in set (0.00 sec)

*/

# 二、锁
# 1、锁的基本概念
/*
锁是用来协调多进程或者多线程并发访问某一资源的机制。
对表的读取不需要加锁，而表的修改可以加锁
*/

# 2、锁的类型
-- ①MySQL中不同的存储引擎所使用的锁是不同的。
# 表级锁：对整个表进行加锁 （MyISAM和MEMORY等存储引擎采用）
# 行级锁：将表分成多个页面，只对某一页面进行加锁（BDB存储引擎采用）
-- 而innodb存储引擎采用表级锁和行级锁，默认是行级锁

# 3、读锁和写锁
-- ①read读锁（共享锁）
# 事务N对对象A加上共享锁S，其他的事务不可修改对象A，但是可以查询A，也可以加共享锁
# 事务N也不能访问其他对象，只能访问加锁的对象

-- ②write写锁（排他锁）
# 事务N对对象A加上共享锁X，其他事务不可读不可写，也不可加锁
# 事务N也不能访问其他对象，只能访问加锁的对象

# 4、MyISAM表级锁测试
-- MyISAM默认用户读取数据时自动加read锁，修改数据时自动加write锁

# ①加锁
-- 基本格式:Lock tables 表名 锁类型; # read/write

# ②解锁
-- 基本格式：unlock tables;

/*
用户A:
mysql> unlock tables;
Query OK, 0 rows affected (0.00 sec)

mysql> lock tables test write;
Query OK, 0 rows affected (0.00 sec)

mysql> select * from test;
+----+-----------------+------+
| id | name            | age  |
+----+-----------------+------+
|  1 | 号卫            |   22 |
|  2 | 梦幻星辰        |   19 |
|  3 | 诚信的筹码      |   20 |
+----+-----------------+------+
3 rows in set (0.00 sec)

mysql> update test set age=28 where id =1;
Query OK, 1 row affected (0.00 sec)
Rows matched: 1  Changed: 1  Warnings: 0

mysql> select * from test;
+----+-----------------+------+
| id | name            | age  |
+----+-----------------+------+
|  1 | 号卫            |   28 |
|  2 | 梦幻星辰        |   19 |
|  3 | 诚信的筹码      |   20 |
+----+-----------------+------+
3 rows in set (0.00 sec)

mysql> unlock tables;
Query OK, 0 rows affected (0.00 sec)

mysql> unlock tables;
Query OK, 0 rows affected (0.00 sec)

用户B：
mysql> select * from test;
+----+-----------------+------+
| id | name            | age  |
+----+-----------------+------+
|  1 | 号卫            |   24 |
|  2 | 梦幻星辰        |   19 |
|  3 | 诚信的筹码      |   20 |
+----+-----------------+------+
3 rows in set (0.00 sec)

mysql> update test set age = 22 where id =1;
Query OK, 1 row affected (27.41 sec)
Rows matched: 1  Changed: 1  Warnings: 0

mysql> update test set age = 22 where id =1;
Query OK, 0 rows affected (0.00 sec)
Rows matched: 1  Changed: 0  Warnings: 0

mysql> lock tables test write;
Query OK, 0 rows affected (13.60 sec)

mysql> unlock tables;
Query OK, 0 rows affected (0.00 sec)

mysql> select * from test;
+----+-----------------+------+
| id | name            | age  |
+----+-----------------+------+
|  1 | 号卫            |   28 |
|  2 | 梦幻星辰        |   19 |
|  3 | 诚信的筹码      |   20 |
+----+-----------------+------+
3 rows in set (13.37 sec)

*/



