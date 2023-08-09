# 游标和条件处理
use tzdb1;
# 一、游标cursor
# 1、游标的基本概念
/*
在查询表时，会获得一个临时结果集，游标就是用来遍历这个结果集中每一条记录的
游标可以返回结果集中的一行或者多行记录
游标只能在存储过程或者函数中使用，并且一次只能指向一条记录。
*/
select * from teacher;

# 2、游标的使用
-- ①声明游标（定义游标）
# 基本格式：declare 游标名 cursor for select查询语句;

-- ②打开游标
# 基本格式：open 游标名;

-- ③遍历游标（使用游标）
# 基本格式：fetch 游标名 into 值列表（变量）；

-- ④释放游标（关闭游标）
# 基本格式：close 游标名;

/*
# 注意：游标在遍历完成临时结果集之后，会指向最后一条记录的下一条记录，
由于下一条没有数据，就会出现no data to fetch的错误。
# 错误处理：为了解决这个错误，就需要定义一个条件处理函数NOT FOUND来捕获这个异常
没有进行异常处理就会报错。
*/

-- 案例1：通过游标遍历teacher表中年龄大于25的数据,并统计数量
delimiter //
create procedure pro_cursor_test()
begin
declare tids int; # 编号
declare tnames varchar(60); # 姓名
declare tsexs varchar(4); # 性别
declare tages int;	# 年龄
declare counts int default 0;	# 统计变量
declare cur_exit bool default false;	# 定义退出变量
declare cursor1 cursor for
select * from teacher where t_age >25;
declare continue handler for not found set cur_exit = true;
open cursor1;
cur:loop
fetch cursor1 into tids,tnames,tsexs,tages;
if cur_exit then leave cur;
end if;
select tids,tnames,tsexs,tages;
set counts = counts +1;
end loop;
select counts;
close cursor1;
end//
delimiter ;

call pro_cursor_test;

# drop procedure pro_cursor_test;

# 二、条件处理
-- 1、条件处理的概念
# 条件处理就是MySQL中的异常处理（错误处理）
/*
MySQL通过条件处理来捕获异常和错误
条件处理只能在存储过程中使用，并且存储过程和条件处理只有MySQL5.5之后的版本才支持
5.5之前的版本不支持存储过程和条件处理
*/

-- 2、定义条件处理函数（？ declare handler）
/*
DECLARE handler_action（处理动作名） HANDLER
    FOR condition_value [, condition_value] ...
    statement（怎么处理）

handler_action: # 处理动作名：出错了是继续执行还是退出
    CONTINUE（继续）  | EXIT（退出）  | UNDO（不做，MySQL不支持）

condition_value: # 错误参数（错误代号） 可以在MySQL官网上查看到相关文档
    mysql_error_code # 错误码
  | SQLSTATE [VALUE] sqlstate_value # 状态值字符串
  | condition_name # 所有以01开头的
  | SQLWARNING	# 所有以02开头的
  | NOT FOUND	# 除了00、01、02开头的
  | SQLEXCEPTION
*/

select * from abcd;
# Error Code: 1146. Table 'tzdb1.abcd' doesn't exist	0.000 sec

-- 3、条件处理练习
# ①无错误处理的存储过程
delimiter //
create procedure pro_test1()
begin
select * from untable;
end//
delimiter ;

call pro_test1;
# Error Code: 1146. Table 'tzdb1.untable' doesn't exist	0.000 sec

# ②在存储过程中用 错误码 进行错误处理
delimiter //
create procedure pro_test2()
begin
declare continue handler for 1146
select '此表不存在' as '错误';
select * from untable;
end//
delimiter ;

call pro_test2;

# 调用存储过程后不会报错，而是按照你所设置的方法进行处理

# ②在存储过程中用 状态值 进行错误处理
delimiter //
create procedure pro_test3()
begin
declare continue handler for SQLSTATE '42S02'
select '此表真的不存在' as 'error';
select * from untable;
end//
delimiter ;

call pro_test3;

# 3、错误条件函数的声明（? declare condition）
/*
DECLARE condition_name（函数名） CONDITION FOR condition_value（错误代码）

condition_value:
    mysql_error_code # 错误码
  | SQLSTATE [VALUE] sqlstate_value #状态值
*/

-- 练习2：
delimiter //
create procedure pro_test4()
begin
declare on_have_table condition for 1146;# 错误码1146可以替换成状态值SQLSTATE '42S02'
declare continue handler for on_have_table
select '此表真的的确不存在呀' as '错误';
select * from untable;
end//
delimiter ;

call pro_test4;

# 错误条件函数相当于给错误取别名，通过别名来处理

# 4、获取错误信息（诊断信息）
# 通过get diagnostics获取错误信息。
/*
-- 基本格式：
get diagnostics condition 错误信息位置
@变量名1 = mysql_errno, # 获取错误码
@变量名2 = returned_sqlstate, # 获取状态值
@变量名3 = message_text; #获取错误信息文本
*/

-- 例如：
drop table untable;

get diagnostics condition 1
@x = mysql_errno,
@y = returned_sqlstate,
@z = message_text;

select @x as 错误码,@y as 状态值,@z as 错误信息;

# 5、更改错误信息
-- ①通过resignal / signal 更改错误信息
# 基本格式：创建一个存储过程是实现错误信息的更改
delimiter //
create procedure pro_test5()
begin
declare on_have_table condition for 1146;# 错误码1146可以替换成状态值SQLSTATE '42S02'
begin signal sqlstate '42S02' # 参数signal需要指定错误信息
set schema_name = '数据库', # 数据库名
table_name = '表名',	# 表名
message_text = '没有这个表', # 错误信息
mysql_errno = 11;	# 错误码
# class_origin # 原始类名
# subclass_origin # 原始子类名
# constraint_catalog # 约束目录
# constraint_name # 约束名
# catalog_name # 目录名
# column_name # 列名
# cursor_name # 游标名
end;
drop table untable;
end//
delimiter ;

call pro_test5;

# Error Code: 11. 没有这个表	0.000 sec

# 更改错误信息还是会报错，但是可以按照你想要的修改相应的提示语句

delimiter //
create procedure pro_test6()
begin
begin resignal 	# 参数resignal默认修改上一条错误信息
set schema_name = '数据库', # 数据库名
table_name = '表名',	# 表名
message_text = '没有这个表', # 错误信息
mysql_errno = 11;	# 错误码
# class_origin # 原始类名
# subclass_origin # 原始子类名
# constraint_catalog # 约束目录
# constraint_name # 约束名
# catalog_name # 目录名
# column_name # 列名
# cursor_name # 游标名
end;
drop table untable;
end//
delimiter ;

call pro_test6;
