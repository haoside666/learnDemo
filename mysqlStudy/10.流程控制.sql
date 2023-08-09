use tzdb1;

# 流程控制
-- 数据库中的流程控制就相当于C语言中的控制语句
-- 其中分为：顺序结构、选择结构、循环结构

# 顺序结构
-- SQL语句是从上至下，从左至右依次执行的
-- begin……end 相当于C语言中的{}，复合语句（语句块）
# begin……end能够嵌套使用么？
-- begin……end能够嵌套使用,但是需要注意局部变量作用域范围的问题

delimiter //
create procedure test1()
begin
declare x int;
set x = 10;
begin
# set x = x+1;
declare y date;
set y = now();
select x,y;
end;
# set y = "2019-11-11";
# select x,y;
end//
delimiter ;

call test1();

drop procedure test1;

if (SELECT COUNT(*) FROM information_schema.KEY_COLUMN_USAGE where constraint_name='for_lessonid')>0 then selece 1 else select 0;

# 二、选择分支结构
# 和C语言中的if else 与 switch类似
# 1、if选择结构
# ①if语句
-- 一般格式：if 判断条件 then 语句; end if; # if之后可以没有括号，执行语句用then,if必须要有结束语句end if;(end if中间必须有空格)
# if x>10 then select 'x大于10'; end if;
# ②if else语句
-- 一般格式：if 判断条件 then 语句1; else 语句2; end if;
# ③if else嵌套
-- 一般格式：if 判断条件 then 语句1; elseif 判断条件 then 语句2; elseif 判断条件 then 语句3;…… else 语句n; end if;
# elseif中间没空格

-- 例如：判断x是否大于100
delimiter //
create procedure test2(in x int)
begin
if x>100 then select "x大于100";
elseif x=100 then select "x等于100";
else select "x小于100";
end if;
end//
delimiter ;

call test2(101);

# 2、case多分支结构
# 相当于C语言中的switch……case语句
/* 一般格式：case 条件值
	when 值1 then 语句1;
    when 值2 then 语句2;
    when 值3 then 语句3;
    ……
	when 值n then 语句n;
    else 语句n+1;
end case;
*/

-- 例如：对成绩进行评分
delimiter //
create procedure test3(in score int)
begin
case score div 10 # floor(score/10) # 强制类型转换	# 整除score div 10 # 不能用round(score/10)
	when 10 then select '满分' 成绩等级;
    when 9 then select '优秀' 成绩等级;
    when 8 then select '良好' 成绩等级;
    when 7 then select '及格' 成绩等级;
    when 6 then select '及格' 成绩等级;
    else select '不及格' 成绩等级;
end case;
end//
delimiter ;

drop procedure test3;

set @s = 100;

select 99/10;

call test3(88);

# 三、循环结构
# C语言中有for、while、do while循环
# 1、while……do循环语句
-- 基本格式：while 条件表达式 do 循环体语句; end while;
# 数据库中while……do循环和C语言中的while循环一样

-- 例如：求数字1到10的和
delimiter //
create procedure test4(out s1 int)
begin
declare i int default 1;
declare s int default 0;
while i<=10 
do set s = s+i; set i = i+1; # SQL语言中没有+=、-=、++、--
end while;
set s1 = s;
end//
delimiter ;

drop procedure test4;

call test4(@s);

select @s as '1到10的和';

# 2、loop循环
-- loop循环的一般格式：loop 循环体语句; end loop;
# 注意：这里的loop循环是一个无限循环(死循环),其没有结束条件,所以需要手动用if添加结束条件
-- loop循环添加结束条件格式：循环别名: loop 循环体语句; if 条件表达式 then leave 循环别名; end if; end loop;
# 这里给循环取别名，通过if语句判断结束条件，leave离开（跳出）循环（相当于C语言中的break）

-- 例如：求整数1到n的和
delimiter //
create procedure test5(out s1 int,in n int)
begin
declare i int default 1;
declare s int default 0;
sum1:loop
set s = s+i; set i=i+1;
if i>n then leave sum1;
end if;
end loop;
set s1 = s;
end//
delimiter ;

drop procedure test5;

call test5(@s,5);

select @s;

# 3、repeat循环
-- 基本格式：repeat 循环体语句; until 条件表达式 end repeat;
# 注意：相同点：repeat相当于C语言中的do while循环,都是先执行一次循环体再判断条件
# 注意：不同点：do while循环是条件不满足时结束循环，而repeat循环与do while循环相反，repeat循环是满足条件时结束循环

-- 例如：求整数n到m的和
delimiter //
create procedure test6(out s1 int,in n int,in m int)
begin
declare i int default n;
declare j int default n+1;
repeat
set i = i+j; set j=j+1;
until j>m # until子句之后的循环结束条件是为真结束循环,until子句之后不能有;分号
end repeat;
set s1 = i;
end//
delimiter ;

drop procedure test6;

call test6(@s,5,10);

select @s;

# 四、跳出循环
-- ①leave
# 跳出并结束整个循环，相当于C语言中的break
# 一般格式：leave 循环别名;

-- ②iterate
# 跳出并结束本次循环，进入下一次循环，相当于C语言中的continue
# iterate只能在循环中使用

/*
以上所说的流程控制只是相当于存储过程和函数而言的，流程控制大多数用于配合存储过程和函数中
*/
