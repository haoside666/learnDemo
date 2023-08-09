# 查询中的自连接查询

# 什么是自连接
/*
也就是自生连接，自连接（self join）是指一个表和其本身进行连接查询的情况，
也是SQL查询语句中经常用到的连接方式，使用自连接可以将自身表的镜像当作另外一个表来对待，
从而得到（产生）一些特殊的数据。
*/

use tzdb4;

create table course(
cou_id int primary key auto_increment,
cou_name varchar(20),
cou_score int,
cou_pid int
)engine innodb default charset utf8;

insert into course values(null,'C语言',4,null),(null,'C++',4,1),
		(null,'win32',6,2),(null,'QT',6,2),(null,'数据库',6,null),
        (null,'Linux',8,2),(null,'网络编程',10,6);

select * from course;

# 查询每一门课程的间接先修课程
# 一、自连接
select first.cou_id 课程编号,first.cou_pid 先修课程号,second.cou_pid 间接先修课 
from course first,course second where first.cou_pid = second.cou_id && second.cou_pid is not null;



