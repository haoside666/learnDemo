# 数据完整性
# 一、数据完整性的概念
# 1、什么是数据完整性
/* 
数据完整性是指存在数据库中的数据要能正确反映实际情况，
规定输入的数据不能是无效值、错误值或者乱码等。
*/

# 2、数据完整性的类型
/*
①实体完整性：标识符或者主键的完整性，使其值唯一
②域完整性：限制类型、格式和取值范围
③引用完整性：保持原表和引用表数据的一致性
④自定义完整性：用户自定义的业务规则
*/

# 3、数据完整性的实现方式
/*
①实体完整性：主键约束、唯一值约束
②域完整性：检查约束、默认值约束、外键约束
③引用完整性：外键约束
④用户自定义完整性：以上约束的自由组合
*/

# 4、什么是约束？
/*
数据的完整性约束就是在创建表的时候约束条件，是用来
限制属性或者表中数据的，也可以通过修改语句修改约束。

约束又分为行级约束和表级约束

非空约束
唯一约束
主键约束
外键约束
检查约束

*/

use db1;

//not null(非空约束)&& auto_increment(自增列) && 默认值约束modify;
//unique(唯一约束) && primary key(主键约束) && foreign key(外键约束) add or drop;

# 二、数据完整性的实现
-- 1、非空约束 关键字：not null
create table teacher(
t_id int not null,
t_name varchar(20) not null,
t_age int,
t_sex varchar(2)
)engine InnoDB default charset utf8;

insert into teacher(t_age,t_sex)values(20,"男");//错误

insert into teacher values(1,"小威",20,'男');

insert into teacher(t_id,t_age,t_sex) values(2,18,'女');//错误

insert into teacher(t_id,t_name) values(2,"夏七");


create table students(
s_id int,
s_name varchar(20),
s_age int,
s_sex varchar(2)
)engine InnoDB default charset utf8;
# 修改表中属性约束不为空
alter table students modify column s_id int not null;
desc students;//查看表信息
# 修改表的方法去掉非空约束
alter table teacher modify column t_name varchar(20);
desc teacher;

-- 2、唯一约束 关键字：unique
# 指定某列或者某几列数据不能重复
# 创建表的同时添加唯一约束
create table teacher(
t_id int not null unique, # 添加非空且唯一约束，自动升级为主键
t_name varchar(20) not null,
t_age int,
t_sex varchar(2)
)engine InnoDB default charset utf8;

# 通过修改语句为指定列添加唯一约束
alter table teacher add constraint uni_tid unique(t_id);
# 数据库默认第一个非空且唯一的属性为主属性（主键）
# constraint 约束名 （给约束取名字）

/*
show keys from 查看该表的约束
如果不取约束名 默认该约束的名称等于该列的名称
如果修改了这列的名称，而约束的名称却不会改变的
通过show keys from查看
*/

desc teacher;
alter table teacher add constraint uni_tname unique(t_name);
insert into teacher values(1,"卫",18,'男');//1已经存在
insert into teacher values(4,"小威",18,'男');//小威已经存在

# 删除唯一约束
alter table teacher drop index uni_tname;//要加上index 否则就是变成了删除该字段的形式
drop index 索引名 on 表名;

# 复合唯一约束（表级约束）
/*
对多个列进行唯一约束，约束两个以上的字段（属性）
不能同时一致,可以存在某些属性一致的情况。&&的关系
*/

/*
create table teacher(
t_id int not null,
t_name varchar(20) not null,
t_age int,
t_sex varchar(2),
constraint uni_tidname unique(t_id,t_name)
)engine InnoDB default charset utf8;
*/
alter table teacher add constraint uni_tidname unique(t_id,t_name);

# 3、主键约束 关键字：primary key
/* 主键约束是非空且唯一的约束，
①一个表只能有一个主键约束（表级约束）
②多列联合主键约束，联合主键的值不能重复
*/
/* 创建主键
create table teacher(
t_id int primary key,
t_name varchar(20) not null,
t_age int,
t_sex varchar(2),
)engine InnoDB default charset utf8;
*/
# 添加主键
alter table teacher add constraint pri_tidname primary key(t_id);
# 创建联合主键
alter table teacher add constraint pri_tidname primary key(t_id,t_name);
# 删除主键约束
alter table teacher drop primary key;
/* 由于一个表只能有一个主键，直接丢掉主键就可以了，
只要规定表名，可以不规定主键约束名*/

# 4、自增列 关键字：auto_increment（行级约束）
/* 自增列在插入数据时，如果不规定属性的值，
其值会根据上一个属性的值自动加一*/
# 创建表时添加自增列
/*
create table teacher(
t_id int primary key auto_increment,
t_name varchar(20) not null,
t_age int,
t_sex varchar(2),
constraint uni_tidname unique(t_id,t_name)
)engine InnoDB default charset utf8;
*/
# 添加自增列
alter table teacher modify column t_id int auto_increment;
desc teacher;
insert into teacher(t_id,t_name) values(null,"红月");
# 自增列默认从1开始
# 在创建表后设置自增列的初始默认值
/*
create table teacher(
t_id int primary key auto_increment=1000,
t_name varchar(20) not null,
t_age int,
t_sex varchar(2),
constraint uni_tidname unique(t_id,t_name)
)engine InnoDB default charset utf8 auto_increment=100;
*/

# 删除自增列
# 删除自增列的方法与之前的方法一致
# alter table teacher modify column t_id int;

# 5、检查约束 关键字：check
# 检查约束就是检查列中属性的取值范围。
# 在创建表后设置检查约束
/*
create table teacher(
t_id int primary key auto_increment=1000,
t_name varchar(20) not null,
t_age int check(t_age>20 and t_age<200),# 规定教师年龄的取值范围
t_sex varchar(2) check(t_sex='男' or t_sex='女'),# 规定教师性别的取值范围
constraint uni_tidname unique(t_id,t_name)
)engine InnoDB default charset utf8 auto_increment=100;
*/
Alter table 表名 add Constraint check(t_age>20 and t_age<200);
# 但是MySQL数据库不支持check检查约束，需要在外部进行判断

# 6、默认值约束 关键字：default
# 默认值约束添加数据时，如果没有给定属性值，会添加一个默认值
# 在创建表后设置默认值约束
/*
create table teacher(
t_id int primary key auto_increment=1000,
t_name varchar(20) not null,
t_age int，
t_sex varchar(2) default '男'，
constraint uni_tidname unique(t_id,t_name)
)engine InnoDB default charset utf8 auto_increment=100;
*/
# 添加默认值约束
alter table teacher modify column t_sex varchar(2) default '男';
insert into teacher(t_id,t_name) values(null,"一人顶三人");

# 删除默认值约束
# 删除自增列的方法与之前的方法一致
alter table teacher modify column t_sex varchar(2);

# 外键约束 foreign key
/*外键约束是指一个表中的属性值参考另一个表中的主属性的值，
也就是外键值参考主键值
由于外键约束是表级约束，所以要在创建表时先创建参考表*/
# 1、创建表时建立外键约束

create table class(
class_id int primary key,
c_name varchar(20) not null,
c_no int
)engine InnoDB default charset utf8;

create table student1(
s_id int primary key,
s_name varchar(20) not null,
s_cid int not null,
s_age int,
s_sex varchar(2),
constraint for_scid foreign key(s_cid) references class(class_id)
)engine InnoDB default charset utf8;

insert into class values(1,'C++',0),(2,'java',0),(3,'python',0);
# 有对应的班级插入成功
insert into student1(s_id,s_name,s_cid)
	values(1,'张三',1),(2,'李四',3);
# 错误 没有对应的班级无法插入
insert into student1(s_id,s_name,s_cid)
	values(3,'王五',4);
    
# 2、添加外键约束
alter table student1 add constraint for_scid foreign key(s_cid) references class(class_id);

# 3、删除外键约束
alter table student1 drop foreign key  for_scid;

# 4、级联更新/删除
# 是指父表中的元组更新或删除等操作对子表的处理方法
# 其中有三种处理方法：
# 在更新/删除中（on update/on delete）
-- ①cascade:父表中的元组更新或删除，在子表中跟着更新或者删除
	# 在语句后加上：on update cascade/on delete cascade
-- ②no action：无动作，若子表中有匹配的记录，就不允许更新/删除父表的数据
	# 在语句后加上：on update no action/on delete no action
-- ③set null：设置为空，若子表中有匹配的记录，更新/删除父表的数据，子表中对应数据设置为空
	# 在语句后加上：on update set null/on delete set null

# 可以同时设置更新和删除所对应的操作
-- 在语句后加上：on update cascade on delete no action
create table student1(
s_id int primary key,
s_name varchar(20) not null,
s_cid int not null,
s_age int,
s_sex varchar(2),
constraint for_scid foreign key(s_cid) 
	references class(class_id)on update cascade on delete set null
)engine InnoDB default charset utf8;
# 2、添加外键约束and级联更新/删除
alter table student1 add constraint for_scid foreign key(s_cid) references class(class_id) on update cascade on delete set null;

