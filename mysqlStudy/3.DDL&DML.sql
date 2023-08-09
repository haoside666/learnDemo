# DDL与DML
-- 单行注释
# 单行注释
/* 多行
注释*/
 
# DDL(Data Dfinition Language) 数据定义语言
# 它是用来定义、管理数据对象（数据库、关系表、视图、索引）的
--0、设置数据库字符集
--alter database 数据库名 default character set utf8;
alter database db2 default character set utf8;
alter table 表名 default character set utf8;
-- 1、创建数据库
# create database 数据库名;
create database db1;
# create database DB1; sql语言不区分大小写
-- create database if not exists DB1;
#如果不存在就创建数据库，存在就不创建
-- create database if not exists DB1 default charset utf8;
-- 2、删除数据库
# drop database 数据库名;
drop database db;
-- 3、使用数据库
# use 数据库名;
use db1;
 
-- 4、创建数据表
/* create table 表名（
属性名1 属性类型1 约束1（可省略）,
属性名2 属性类型2 约束2（可省略）,
属性名3 属性类型3 约束3（可省略）,
……
属性名n 属性类型n 约束n（可省略））
engine innodb default charset utf8;
*/
 
/*属性类型 数据类型
数值类型
tinyint     1   迷你整型
smallint    2   小整型
mediunint   3   中等整型
int         4字节 整型
bigint      8字节 大整形
float       4字节 单精度
double      8字节 双精度
 
字符类型 '' ""
char        1字节 定长字符串
varchar     2字节 变长字符串
 
char(10)        不管你输入多少个字符，总是占10个字节
varchar(10)     输入多少占多少，最多存10个字节
 
tinytext
mediumtext
text        文本字符串
longtext
tinyblob
mediumblob
blob        二进制字符串
longblob
 
日期时间类型
date        日期      YYYY-MM-DD 年-月-日
time        时间      HH:MM:SS 时-分-秒（24小时制）
datetime    日期时间    YYYY-MM-DD HH:MM:SS
%Y-%m-%d %H:%i:%s:
*/
 
create table if not exists students(
s_id int,
s_name varchar(20),
s_sex varchar(2),
s_bir date
)engine innodb default charset utf8;
 
# 查看表结构
desc students;
show columns from students;
 
#修改表结构
-- 1、增加表中列
# alter table 表名 add 属性名 属性类型（数据类型）;
alter table students add s_cid int;
-- 2、修改表中列
# alter table 表名 modify 属性名 属性类型;
alter table students modify s_name varchar(30);
-- 3、删除表中列
# alter table 表名 drop  属性名;
alter table students drop s_cid;
 
# 删除表
drop table 表名;
 
# DML(Data Manipulation Language)数据操纵语言
# 是用来操纵数据对象中数据的
# 插入数据
/*
insert into 表名(属性名1,属性名2,属性名3,……,属性名n)
            values(属性值1,属性值2,属性值3,……,属性值n);
*/
 
# 插入单条数据
insert into students(s_id,s_name)
            values(1,'小威');
# 插入多条数据
insert into students(s_id,s_name)
            values(2,'小萝卜'),(3,"笑书生"),(4,"一人顶三人");
# 插入全部数据
insert into students
            values(2,'euyey','男','2019-11-30');
 
# 修改数据
# 修改所有数据
/*
update 表名 set 属性名1=属性值1,属性名2=属性值2,属性名3=属性值3;
*/
update students set s_name='一亩';
# 条件更新
update 表名 set 属性名1=属性值1,属性名2=属性值2,属性名3=属性值3
            where 条件表达式;
update students set s_name='小威' where s_id = 1;
# 多条件更新
/*
update 表名 set 属性名1=属性值1,属性名2=属性值2,属性名3=属性值3
            where 条件表达式1 &&（and） [||(or)] 条件表达式2;
*/
update students set s_name='笑书生' where s_id = 2 && s_sex='男';
 
# 删除数据
# 1、全部删除
# 基本格式：delete from 表名;
delete from students;
truncate table students;//清空表数据
# 2、条件删除alter
# 基本格式：delete from 表名 where 条件表达式;
delete from students where s_id=2 && s_sex='男';


#查看数据
#1.全部查看
#基本格式:select *from 表名;
#2.查看一行或几行
#基本格式:select * from 表名 limit 0,1; 0表示从第一行开始 1表示访问的行数  ---->这里只访问第一行
#3.查看一列或几列
#基本格式: select 字段1 , 字段2 from 表名;