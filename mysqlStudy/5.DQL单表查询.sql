# DQL单表查询
# DQL 数据查询语言，用于对数据库中关系表的数据进行查询的语句，支持多种查询方式。
use db1;
# 数据查询语言关键字：select
# 查询语句的一般格式：select 属性名 from 数据库名.表名;
-- 1、查询所有字段
select * from students;
# 查询所有字段用*
# select * from sys.Tables;
-- 2、查询指定字段
select s_id,s_name from students;
-- 3、条件查询
/*
1、条件运算符：>、<、=、!=(<>)、>=、<= （不存在==）

2、逻辑运算符：&&(and/AND)、||(or/OR)
select *from 表名 where id>1 && id<3;

3、between……and…… 在……范围内
not between……and…… 在……范围外
select *from 表名 where  id  not between 1 and 3;

4、like 用于字符串匹配（通配符%和_）模糊匹配
%：匹配任意0个、1个或多个字符
_: 匹配任意一个字符
select *from 表名 where 字段 like '_';//用于字符串

5、in 在集合范围内查找
not in 在集合范围外查找
select *from 表名 where age in (10,11);
# 一般不用in，由于in的内部处理没有where好

6、is null 查询空值
is not null 查询非空值 (不能用not is null)
select *from 表名 where age is null;

7、distinct查询去重
同一个查询语句中只能对一个属性去重
select distinct 字段 from 表名;

8、limit [偏移量n,] 记录条数m 分页查询 （中括号[]中的参数可要可不要）
偏移量是指从第n+1条开始后m条数据
select *from 表名 limit 偏移量,记录条数;

9、union/union all合并查询结果
用于合并多个select语句的结果，
要求每一个select查询语句返回的临时结果集（虚拟表）的列相同
union和union all区别：union是去重的，而union all 不去重，显示所有
临时结果集（虚拟表）：不是实际存在的原表，他不占有存储空间
保存至内存中的临时表

*/
select * from students where s_id = 1;
select * from students where s_id > 1;
select * from students where s_id = 1 or s_name = '小萝卜';
select * from students where s_id between 2 and 3;
select * from students where s_id not between 2 and 3;
select * from students where s_name like '小%';
select * from students where s_name like '小_';
select * from students where s_name like '小__';
select * from students where s_name like '%小%';
select * from students where s_name like '_小_';
select * from students where s_name like '_书_';
select * from students where s_name like '%_书_';
select * from students where s_id in(1,3,5,6,7);
select * from students where s_name in('小威','张三','小萝卜');
select * from students where s_id not in(1,3,5,6,7);
desc students;
insert into students values(5,'张三','男','2000-1-1'),
(6,'李四','男','2000-1-2'),(7,'张三','男',null);

select * from students where s_sex is null;
select * from students where s_bir is not null;
#select * from students where s_bir not is null;不能用not is null

insert into students values(8,'张三','男','2000-1-1'),
(9,'小威','男','2000-1-2'),(7,'笑书生','男',null);

select distinct s_name from students;

select * from students limit 3; # 查询前三条记录
select * from students limit 2,3; # 查询从第3条记录开始的后3条记录
select * from students limit 1,4; # 查询从第2条记录开始的后4条记录

select 'a',1;
select 'b',2;
select '小威',123456;
select 'b',2,'小萝卜';

select 'a',1 union select 'b',2 union select '小威',123456;
select 'a',1 union select 'b',2,'小萝卜';	# 列不同不能合并
select * from students where s_id = 1 union select * from students where s_id between 1 and 3;
select * from students where s_id = 1 union all select * from students where s_id between 1 and 3;

# 创建表参考另一个表（表的复制/备份）
# 通过查询结果集新建表，注意创建的新表没有约束（不会复制约束）
create table newstudents(select * from students);
desc students;
desc newstudents;
select * from newstudents;

create table newstudents2(select s_id,s_name from students);
select * from newstudents2;

# 通过查询结果集插入数据
insert into newstudents(s_id,s_name) select * from newstudents2;
insert into newstudents2 select 10,'王五';
insert into newstudents2 select 12,'莫名' union select 11,'赵六';

# 用as关键字取别名
select s_id as 学号,s_name as 姓名 from newstudents;
# as可以省略
select s_id 学号,s_name 姓名 from newstudents;

# order by排序(默认升序)
select s_id 学号,s_name 姓名 from newstudents order by s_id;
# order by 属性名 desc;(desc 降序排序)
select s_id 学号,s_name 姓名 from newstudents order by s_id desc;

# group by 分组查询 (需要主键约束)
select s_name 性别 from newstudents group by s_name;
# group by 之后的条件查询不能用where,而只能用having
select s_name 性别 from newstudents group by s_name having s_name = '小威';

select s_name 性别 from newstudents where s_id=7 group by s_name ;
select *from 表名 where 字段满足什么条件 group by 字段;

select s_id 学号,s_name 姓名 from student1 group by s_id;