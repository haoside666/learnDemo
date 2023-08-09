# 数据库函数
# 数据库的库函数，在数据库中提供了一些用于实现特定功能的函数 

# 一、聚合函数
# 聚合函数就是对一组值进行计算，返回单个值
-- 1、count
# 计数函数，对元组或者属性计数
# 一般格式：count(属性名)
select count(字段) from class;

update class set class.c_stunumber = (select count(s_id) from student where s_cid = 3)
where class.c_id = 3;

-- 2、求最大值函数max
# 一般格式：max(属性名)
select max(class.c_id) from class;

-- 3、求最小值函数min
# 一般格式：min(属性名)
select min(class.c_id) from class;

-- 4、求平均数函数avg
# 一般格式：avg(属性名)
select avg(class.c_id) from class;
select avg(class.c_tid) from class;

-- 5、求和函数sum
# 一般格式：sum(属性名)
select sum(class.c_id) from class;

# 以上函数只计算有效值，不计算空NULL值

# 二、日期时间函数
-- 1、求当前的日期和时间now 数据类型为：日期时间
# 一般格式：now() 
select now();

-- 2、获取日期时间类型中的日期date
# 一般格式：date(日期时间类型)
select date(now());
select date("2000-1-1 6:6:6");
select date("2000/1/1 6@6@6");

-- 3、获取日期时间类型中的时间time
# 一般格式：time(日期时间类型)
select time(now());
select time("2000-1-1 6:6:6");
select time("2000*1*1 6&6&6");

select year(now()); # 年
select month(now()); # 月
select day(now()); # 日
select hour(now()); # 小时
select minute(now()); # 分钟
select second(now()); # 秒钟
select week(now()); # 星期

-- 4、时间日期类型转字符串类型函数date_format
# 一般格式：date_format(日期时间类型,格式化字符串);
select date_format(now(),'%y/%m/%d-%h:%i:%s');
select date_format(now(),'%Y-%M-%D %h_%i_%s');
# 格式化字符串的风格符可以自定义
# mysql不区分字母大小写，但是字符串中除外

# 三、常用的一般函数
-- 1、小写字母转大写字母函数upper
select upper('abcDEF123');
select ucase('abcDEF123');

-- 2、大写字母转小写字母函数lower
select lower('abcDEF@#$');
select lcase('abcDEF@#$');

-- 3、提取字符串函数，substring
# 以给定的参数求字符串中的一个子串
# 一般格式：substring(字符串,start,lenth)
select substring('abc123!@#DEF',4,3);
# 从字符串中第start个字符开始取出长度为lenth的一个子串
select mid('abc123!@#DEF',1,3);

-- 4、四舍五入函数round
# 一般格式：round(数值类型[,精确位数]);
select round(1234.5678); # 不规定精确位数，只保留整数，小数四舍五入
select round(1234.5678,2); # 规定精确位数

-- 5、求次方函数power
# 一般格式：power(底数,指数)
select power(2,3);
select sqrt(16); # 求平方根

select sqrt(sqrt(16));

# 举一反三：怎么求次方根？
select power(16,1/4);

select power(27,round(1/3,2)); # 1/3 = 0.333333…… 内存是有限的无法存储无限循环小数

select power(4,0.5);

select power(27,0.3333333333333333);

select power(0,3);



# 嵌套查询(子查询) 条件嵌套
# 嵌套查询可以主外键关系，只是进行数值上的比较
select student.s_id,student.s_name,student.s_cid from student
where student.s_cid in 
(select class.c_id from class where class.c_id = 1);

select student.s_id,student.s_name,student.s_cid from student
where student.s_cid in 
(select class.c_id from class where class.c_tid in
(select teacher.t_id from teacher where teacher.t_name = '小威')
);

# from子句后以查询结果集作为参考表进行查询
select * from class where class.c_id in
(select S.s_cid from (select student.* from student where student.s_age = 18) S where S.s_id in (1,2));

