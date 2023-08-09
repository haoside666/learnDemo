小可爱们记得填写一下满意度调查链接哦
第7期数据库满意度调查链接
https://jinshuju.net/f/LnM7jw
么么哒>_<

# 视图和索引
# 方便用户执行查询操作

use tzdb1;

# 一、提高SQL查询效率
# 查询语句也有查询效率
-- 1、选择有效的表名顺序
/* select语句一般优先处理写在from子句最后的表
将记录条数最少的或者是父表（被参考表）放在最后可提高查询效率
*/
select class.c_name 班级名称,teacher.t_name 班主任
from class left join teacher on class.c_tid = teacher.t_id order by class.c_id;
#如这里先处理teacher表在处理class表--->将记录条数最少的或者是父表（被参考表）放在最后可提高查询效率

-- 2、select语句中尽量避免使用*
/* 如果不需要查询所有字段，尽量的把需要查询的字段一一写出来，
而不是用*代替*/
-- 3、整合简单的查询语句
select class.c_id from class;
select class.c_name from class;
# 以上两条查询语句可以合并成下面一条查询语句
select class.c_id,class.c_name from class;
/* 能一次性查询出来的属性就不要分为两次或多次了*/
-- 4、尽可能的用where替换having
-- 5、尽量多用内部函数，少用运算符自己进行操作
-- 6、多使用表的别名，以减少解析时间
-- 7、尽量用>=代替>等。
/*如：查询>6和查询>=7，效果是差不多的
但是>6先找的6，而>=7是先找的7，相当于多找了一个数
*/
-- 8、尽量使用exists,not exists代替in,not in

# 二、视图
-- 1、视图的创建
# 视图关键字：view
# 创建视图一般格式：create view 视图名 as 查询语句;
select * from student;
create view V_S as select * from student;
# 2、视图的基本使用
select * from V_S;

select student.s_id,student.s_name from student;
create view V_Sidname as select student.s_id,student.s_name from student;
select * from V_Sidname;

# 3、什么是视图？视图有什么用？
/* 视图就是可以用于代替一个查询语句，
多次使用同一个查询语句时，可以为此查询语句创建一个视图，方便后续使用
视图就相当于为一个查询结果集（虚拟表）创建一个快捷方式
*/

# 4、视图的修改
-- 修改视图的一般格式：alter view 视图名 as 查询语句;
alter view V_S as select student.s_name,student.s_sex,student.s_age from student where student.s_id>6;
select * from V_S;

# 5、删除视图
-- 删除视图一般格式：drop view 视图名;
drop view V_Sidname;
select * from V_Sidname;	# 删除视图后，不能使用对应的视图

# 6、为什么要使用视图？建立视图的优点和好处
-- ①由于有些查询语句又长有麻烦，并且经常使用，可以给它创建一个视图，以便后续操作。
-- ②用户只关心数据，而不关心过程，面向结果，而不是面向过程
-- ③数据的安全性
/*
视图可以单独设置权限，表中有些数据不方便给用户看，
视图能使用户只能看到表中部分数据，而没办法看到全部数据，
和表结构以及表与表之间的联系，相当于一个保密作用。
*/
-- ④数据独立：
/*
视图一旦确定，原表中其他数据的修改很难影响到视图alter
除非修改或者删除了试图在涉及到的字段或属性值。
*/

# 三、索引 index
-- 1、什么是索引
/* 所谓索引，可以将其理解成书的目录一样，相当于一个快捷查询*/

-- 2、索引是用来做什么的？
/* 
索引是用于提高查询效率的，
对需要频繁查询的字段建立索引，比普通字段查询的速度要快一些
*/
# 索引只是用来增加查询效率的，除此之外没有其他用处

-- 3、索引与存储引擎
/*
在MySQL中，索引与存储引擎相关，
也就是索引是存储引擎级别的概念，索引的数据也是需要存储在硬盘中的
不同的存储引擎对索引的实现方式是不同的，也就是存储的数据结构不同
*/
# 查询速度快
-- ①MyISAM（MySQL默认）和InNODB:支持BTREE（B树）索引，数据是以B树的形式存储的
-- ②Memory和Heap:支持BTREE和HASH（哈希表）索引，数据是以哈希表的形式存储的

# 4、索引的分类
-- ①普通索引：允许定义索引的字段重复和空值
-- ②唯一索引：允许定义索引的字段空值，但不能重复
-- ③主键索引：不允许定义索引的字段重复和空值
-- ④全文索引：用于查询文本中的关键字（只有MyISAM支持），只有char、varchar、text类型才可以定义
-- ⑤空间索引：对空间数据类型建立索引

# 5、普通索引
-- ①创建普通索引
-- 一般格式：create index 索引名 on 表名(字段1[,字段2,字段3,……,字段n]);
create index I_Tname on teacher(t_name,t_age);

-- ②以修改的方式创建索引
alter table student add index I_Sname(s_name);

-- ③删除索引
# 一般格式：drop index 索引名 on 表名;
drop index I_Tname on teacher;

-- ④查看表中所有索引
# 一般格式：show index from 表名;或者show kyes from 表名;
show index from teacher;
# 注意：没有建立索引的表存不存在索引呢？
-- 是存在索引的：至少会存在一个主键索引
show index from student;
show index from class;

# 6、主键索引
/*创建主键和外键约束时会自动创建主键索引，无法手动创建*/
# 所以查询主键或者外键时速度会更快一些

# 7、唯一索引
/*创建唯一约束时会自动建立唯一索引，无法手动创建*/
# 有唯一约束的字段查找速度会更快

# 8、全文索引fulltext
# ①创建全文索引
-- 一般格式：alter table 表名 add fulltext(字段1[,字段2,字段3,……,字段n]);
alter table class add fulltext(c_name);
# 全文索引很少用到

# 9、空间索引
/*有涉及到空间类型，一般只有制作地图或者制作模型的软件有涉及到*/

# 10、索引的优缺点
-- ①优点：使用索引可以大大提高查询效率。
# 既然建立索引能提高查询效率，那可以对每个字段都建立么？
-- ②缺点：
 /*由于定义了索引的字段与普通字段相比，存储的数据结构有所差异，
对数据的增加、删除、修改等操作时（不友好），数据库需要进行动态维护
*/
# 动态维护：就是要算出数据的位置在哪（哈希表可能存在哈希冲突）
/* 索引占磁盘空间*/
# 所以建立索引会降低数据维护的速度

# 由索引的优缺点来看：建立索引方便了查询，而增加删除和修改不方便
/*
1、对于数据量小和经常修改、删除或增加的列避免使用索引
2、对于需要频繁查询的字段应该创建索引
3、最适合建立索引的列是where子句中的列，而不是select里的列，也就是建立索引要精准
*/
