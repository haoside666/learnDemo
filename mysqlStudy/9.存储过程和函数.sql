use tzdb1;

# 一、存储过程和函数的概念
# 存储过程和函数类似，都是一个事先编号的存在数据库中的SQL语句集合
-- 用来简化开发人员的工作，减少数据在数据库和应用服务器之间的传输，提高处理效率

# 二、存储过程和函数的区别
# 既然都可以理解成函数，就会有值的传入和传出
# 其中存在的区别为：
-- 存储过程： 参数的传递（参数类型）能用IN、OUT、INOUT
	# 存储过程没有返回值。
-- 函数：只能使用IN，并且必须要有返回值。

# 三、存储过程（？procedure）?问号查看帮助文档
# 1、无参存储过程
-- ①创建无参存储过程
-- 一般格式：create procedure 存储过程名()SQL语句;
-- create procedure select_stu()
-- select * from student;
# 2、调用存储过程
-- 一般格式：call 存储过程名();
-- call select_stu();
# 3、查看存储过程属性详细信息
-- show create procedure select_stu;
# 4、删除存储过程
-- 一般格式：drop procedure 存储过程名;
-- drop procedure select_stu;
# 5、修改存储过程
-- 需要删除后重新创建

# 无参存储过程示例：
# delimiter重定义结束符
/*
delimiter //
create procedure select_1()
begin
select * from student;
select * from class;
select * from teacher;
end//
delimiter ;	# 把结束符改回;分号

call select_1();
*/
# 6、带参的存储过程
-- ①创建带参的存储过程
# 一般格式：
/*
create procedure 存储过程名
(IN[OUT][INOUT] 形参名1 数据类型1,IN[OUT][INOUT] 形参名2 数据类型2,……,IN[OUT][INOUT] 形参名n 数据类型n)
begin
SQL语句;
end;
*/
delimiter $$
create procedure select_stuid(in stu_id int)
begin
select * from student where s_id = stu_id;
end$$
delimiter ;

call select_stuid(6);

desc teacher;

delimiter @@
create procedure select_tea(in tea_id int,in tea_name varchar(60))
begin
insert into teacher(t_id,t_name)values(tea_id,tea_name);
select * from teacher where t_id = tea_id;
end@@
delimiter ;

call select_tea(8,'张三');

# 数据库变量
-- 1、变量的分类
/*
①局部变量：只能在begin……end之间使用
②全局变量：系统自带的，是用来保存数据库当前服务的默认数据，当前服务有效，重启服务后恢复默认值
③会话变量：系统自带的，是用来保存数据库当前会话的默认数据，当前连接有效，重新连接就恢复默认值
④用户变量：全局范围内都有效，相当于C语言中的全局变量
*/
# 局部变量
-- 定义用户变量的一般格式：declare 局部变量名 数据类型;
-- 给局部变量赋值：set 局部变量名 = 值;
delimiter //
create procedure sum1(in x int,in y int)
begin
declare z int default 1;	# default给定默认值
set z = x+y;
select z as "两个数的和为";
end//
delimiter ;

-- declare n int; # 局部变量只能在begin……end之间使用

call sum1(10,20);

# 用户变量
-- 定义用户变量一般格式：set @变量名 = 初始值;
set @a = 10;
select @a;
set @a = 'abc';
select @a;
set @b = 20;
set @sum2= @a+@b;
select @sum2;
# 用户变量是弱类型的，可以支持多种数据类型

delimiter //
create procedure sum_(in x int,in y int,out z int)
begin
set z = x+y;
end//
delimiter ;

set @a = 50;
set @b = 60;
call sum_(@a,@b,
2);
select @sum2;

# 全局变量和会话变量
use mysql;
desc user;

# 五、自定义函数
# 1、创建自定义函数：
/*
delimiter //
create function 函数名(函数参数 数据类型)
returns 函数返回值类型
begin
return(函数返回值语句);
end//
delimiter ;
*/

# 2、调用函数
-- select 函数名(函数参数);

# 3、删除函数
-- drop function 函数名;

# 自定义函数示例
delimiter //
create function sum_n(x int,y int)
returns int
begin
declare z int default 0; # default给定默认值
set z = x+y;
return(z);
end//
delimiter ;

set @a = 100;
set @b = 200;
select sum_n(@a,@b);

set @a = 66;
set @b = 88;
set @sum2 = (select sum_n(@a,@b));

select @sum2;
