# 触发器

# 一、触发器
-- 1、触发器的基本概念
# 触发器是和表相关联的一个数据库对象，是一种特殊的存储过程
-- ①触发器关键字：trigger
-- ②触发器的基本作用：通过对表进行数据插入、更新、删除等操作时触发，用于执行某些操作的。

-- 2、触发器创建
# ? create trigger（？问号查看帮助文档）
/*
CREATE TRIGGER trigger_name(触发器名)
   trigger_time（触发时机{ BEFORE | AFTER }）
   trigger_event（触发条件{ INSERT | UPDATE | DELETE }）
    ON 表名 FOR EACH ROW（对每一行）
    trigger_body（执行的操作）

trigger_time: { BEFORE | AFTER }(之前|之后)

trigger_event: { INSERT | UPDATE | DELETE }（插入|更新|删除）

trigger_order: { FOLLOWS | PRECEDES } other_trigger_name
*/

create database tzdb2;

use tzdb2;

/*
3、 对象new和old（新值和旧值）
new对象存储的是插入或修改操作时，数据表中的新数据（新插入或修改的数据）
old对象存储的是修改或删除操作时，数据表中的旧数据（修改或删除之前的旧数据）
before:可以对new进行修改，after不能对new进行修改
数据库有6种触发器，分为3大类，分别为：
①、before insert,after insert: 没有old对象，只有new对象
②、before update,after update:	既有old对象，也有new对象
③、before delete,after delete:	有old对象，没有new对象
*/

-- 例题1：利用触发器实现检查约束check
# 对下表创建一个触发器，规定学生年龄不能低于0岁，低于0岁的用0代替，不能高于100岁，高于100岁的用100代替。
create table students(
id int primary key auto_increment,
age int
)engine innodb default charset utf8;

delimiter //
create trigger tri_students_insert
before insert on students for each row
begin
if new.age < 0 then set new.age = 0;
elseif new.age > 100 then set new.age = 100;
end if;
end//
delimiter ;

insert into students values(null,20);

select * from students;

insert into students values(null,-10);

insert into students values(null,111);

# 4、删除触发器
-- 基本格式：drop trigger 触发器名;

# 5、MySQL中查看触发器
/*
mysql中触发器是存在information_schema.triggers表中的，
所以查看触发器需要查询information_schema数据库中的triggers表。
*/
show databases;

# 进入information_schema数据库
use information_schema;	

show tables;

# 查询当前数据库中所有触发器
select * from triggers; 

# 查询当前数据库中指定名称的触发器
select * from triggers where trigger_name='tri_srudents_insert';

# 例题2；使用触发器制作日志
-- ①创建日志表
create table review(
id int primary key auto_increment,
username varchar(66),
action_name varchar(20),
action_time datetime
)engine innodb default charset utf8;

-- ②创建触发器
delimiter //
create trigger tri_review_insert
after insert on students for each row
begin
insert into review values(null,user(),'insert',now()); # user()函数获取当前操作的用户名
end//
delimiter ;

insert into students values(null,18);

select * from students;

select * from review;

delimiter //
create trigger tri_review_update
after update on students for each row
begin
insert into review values(null,user(),'update',now()); # user()函数获取当前操作的用户名
end//
delimiter ;

delimiter //
create trigger tri_review_delete
after delete on students for each row
begin
insert into review values(null,user(),'delete',now()); # user()函数获取当前操作的用户名
end//
delimiter ;

# 6、触发器的使用限制
/* 不是任何语句都可以使用触发器来执行
①触发器中不能使用将数据返回的存储过程和函数，也不能使用select、create和call等动态SQl语句
②触发器中不能使用开始和结束事务(事务之后的课程会讲到).
③触发器中不建议写得太复杂，否则数据表每改变一行，所执行的触发器任务就太多了。（不是强制性的）
④触发器中一条语句出现错误，整个触发器就不会执行。
*/
delimiter //
create trigger tri_test
after insert on students for each row
begin
-- insert ？？？
-- update ？？？
select * from review;	# 错误1：触发器中不能使用返回查询结果集的select语句
insert aifhoaifhiouwqehr;   # 错误2：触发器中一旦一条语句出现错误，整个触发器就不会执行
-- ？？？
end//
delimiter ;
# Not allowed to return a result set from a trigger	0.000 sec

# 8、突破触发器的使用限制
/* 虽然触发器中不能使用select查询语句查询数据，也不能直接通过参数返回，alter
但是可以通过用户变量带回数据。
*/

-- 例如：创建触发器带回一个参数
delimiter //
create trigger tri_test_students
before delete on students for each row
begin
select students.age from students 
where old.id = students.id into @ages;# 通过用户变量带回参数
end//
delimiter ;

delete from students where students.id = 4;

select @ages;

delimiter //
create trigger tri_test
after insert on students for each row
begin
create database if not exists test2;
end//
delimiter ;
# Error Code: 1303. Can't create a PROCEDURE from within another stored routine	0.000 sec
# 不能在触发器中执行创建语句
