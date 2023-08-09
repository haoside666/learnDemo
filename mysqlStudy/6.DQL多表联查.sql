# 多表联查
/*
在现实生活中，查询往往涉及到多个表中的数据，
这就需要用到多表查询了
*/

create database tzdb1;

use tzdb1;

create table teacher(
t_id int primary key auto_increment,
t_name varchar(60) not null,
t_sex varchar(4) check(t_sex='男' or t_sex='女'),
t_age int check(t_age>0 and t_age<200)
)engine innodb default charset utf8;

create table class(
c_id int primary key auto_increment,
c_name varchar(50) not null,
c_tid int,
c_stunumber int default 0,
constraint for_CT foreign key(c_tid)
references teacher(t_id)
)engine innodb default charset utf8;

create table student(
s_id int primary key auto_increment,
s_name varchar(60) not null,
s_cid int,
s_sex varchar(4),
s_age int check(s_age>0 and s_age<200),
constraint for_SC foreign key(s_cid)
references class(c_id)
)engine InnoDB default charset utf8;

insert into teacher values(null,'小威','男',26),
(null,'夏七','男',28),(null,'三笠','女',18),
(null,'罗伯特','男',30),(null,'C罗','男',26),
(null,'龙卷风','男',29),(null,'南极星','女',18);

select * from teacher;

insert into class(c_id,c_name,c_tid)values(null,'C语言',3),
(null,'C++',2),(null,'QT',5),(null,'数据库',1),
(null,'win32',4),(null,'linux',null),
(null,'网络编程',null);

select * from class;

insert into student 
select null,'红月',1,'男',18 union all
select null,'枯叶',2,'男',16 union all
select null,'你好',4,'男',19 union all
select null,'小花',3,'女',18 union all
select null,'张三',4,'男',20 union all
select null,'李四',1,'男',21 union all
select null,'王五',3,'男',18 union all
select null,'甜馨',4,'女',16 union all
select null,'赵六',1,'男',23;

select * from student;

# 1、交叉连接
select class.*,teacher.*
from class,teacher order by class.c_name;

select class.c_name 班级名称,teacher.t_name 班主任 
from class,teacher order by class.c_name;

# 条件交叉连接
select class.c_name 班级名称,teacher.t_name 班主任
from class,teacher where class.c_tid = teacher.t_id order by class.c_name;

-- 笛卡尔积：就是多个表中所有数据都相互匹配一次

# 2、内连接 inner join
/*
使用比较运算符，根据表中匹配的字段，
列出与连接体匹配的数据，只有匹配的数据才能查询出来
*/
select class.c_name 班级名称,teacher.t_name 班主任
from class inner join teacher on class.c_tid = teacher.t_id order by class.c_name;
/*
内连接与交叉连接的区别
交叉连接会先产生笛卡尔积，而内连接先执行on筛选条件，不产生笛卡尔积
产生笛卡尔积会影响查询性能，所以一般用内连接代替交叉连接
*/

# 3、外连接
/*
外连接是对内连接进行筛选
*/
/*外连接又分为
左外连接（左连接）
右外连接（右连接）
全外连接（全连接）
*/

/*4、左连接：left join
以左表为基准，显示左表所有记录
右表只显示匹配记录，没有匹配的用null代替
*/
select class.c_name 班级名称,teacher.t_name 班主任
from class left join teacher on class.c_tid = teacher.t_id order by class.c_id;

select class.c_name 班级名称,teacher.t_name 班主任
from teacher left join class on class.c_tid = teacher.t_id order by class.c_id;

/*5、右连接：right join
以右表为基准，显示右表所有记录
左表只显示匹配记录，没有匹配的用null代替
*/
select class.c_name 班级名称,teacher.t_name 班主任
from class right join teacher on class.c_tid = teacher.t_id order by class.c_id;

select class.c_name 班级名称,teacher.t_name 班主任
from teacher right join class on class.c_tid = teacher.t_id order by class.c_id;

# 右链接和左连接没有特别限制，可以相互转换
select class.c_name 班级名称,teacher.t_name 班主任
from class left join teacher on class.c_tid = teacher.t_id order by class.c_id;

select class.c_name 班级名称,teacher.t_name 班主任
from teacher right join class on class.c_tid = teacher.t_id order by class.c_id;

# 6、全连接 full join
# 全连接走游标不做限制，显示全部数据，没有匹配的数据用null代替
select class.c_name 班级名称,teacher.t_name 班主任
from class full join teacher on class.c_tid = teacher.t_id order by class.c_id;
-- 注意：MySQL不支持全外连接

# 利用左连接和右连接实现全连接
select class.c_name 班级名称,teacher.t_name 班主任
from class left join teacher on class.c_tid = teacher.t_id
union
select class.c_name 班级名称,teacher.t_name 班主任
from class right join teacher on class.c_tid = teacher.t_id;

# 7、多表联查
/*
select 表1.属性1,表2.属性2,表3.属性3,……,表n.属性n
from 表1 连接(inner/left/right join)表2 on 连接条件1
	连接(inner/left/right join)表3 on 连接条件2
    ……
    连接(inner/left/right join)表n on 连接条件n-1
*/

# 查询所以学生对应的班级名称及班主任
select s_name 学生姓名,c_name 班级名称,teacher.t_name 班主任 
from student left join class on student.s_cid = class.c_id
	      left join teacher on class.c_tid = teacher.t_id order by class.c_id;

# 多表连接时应注意连接表和连接条件的外键关系
# 只有表中属性互相有关系的表才可以进行连接
/* 
多表连接虽然可以实现多个表中数据的查询，
但是如果有涉及到4个表以上的联查，
就是数据库的设计存在问题了。
一般的连接查询最好不要超过4个表。
*/
# 8、给表取别名：as
select S.s_name 学生姓名,C.c_name 班级名称,T.t_name 班主任
from student as S left join class as C on S.s_cid = C.c_id
	left join teacher as T on C.c_tid = T.t_id order by C.c_id;

/* 给表取别名之后，
当前select语句中所有的表名都只能使用别名，
而不能使用原表名了
*/
# as可以省略
select S.s_name 学生姓名,C.c_name 班级名称,T.t_name 班主任
from student S left join class C on S.s_cid = C.c_id
	left join teacher T on C.c_tid = T.t_id order by C.c_id;
