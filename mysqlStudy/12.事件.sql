use tzdb2;

# 事件

# 一、事件的基本概念
-- 事件与触发器类似，都是在特定的条件下执行某些操作
-- 但是不同的是，触发器是触发时执行操作，而事件是定时执行操作的

# ①事件关键字：event
# ②基本作用：让数据库定时执行某些操作

# 二、事件的创建（？ create event）
/*
CREATE EVENT [IF NOT EXISTS] event_name（事件名称）
    ON SCHEDULE（在事件调度器上）schedule
    [ON COMPLETION [NOT] PRESERVE] # 事件的到期处理
    （事件执行完之后默认保留的，加上'ON COMPLETION NOT PRESERVE'使事件到期后删除）
    [ENABLE 打开 | DISABLE 关闭] # 事件的状态，默认是打开的
    DO event_body（执行的操作）;

schedule:
    AT timestamp [+ INTERVAL interval] ...（AT 时间点 [+ INTERVAL 间隔多久]）
  | EVERY interval	（EVERY 时间段\时间间隔）
    [STARTS timestamp [+ INTERVAL interval] ...]（STARTS 开始时间 [+ INTERVAL 间隔多久]）
    [ENDS timestamp [+ INTERVAL interval] ...]（ENDS 结束时间 [+ INTERVAL 间隔多久]）
# 只有erery有starts和ends这两个参数，而at是没有的

interval:
    quantity {YEAR | QUARTER | MONTH | DAY | HOUR | MINUTE |
              WEEK | SECOND | YEAR_MONTH | DAY_HOUR | DAY_MINUTE |
              DAY_SECOND | HOUR_MINUTE | HOUR_SECOND | MINUTE_SECOND}
*/

# 例如：创建一个事件，每隔6秒钟自动向表中插入一条数据
-- ①创建事件测试表
create table event_test_table
(
id int primary key auto_increment,
insert_time datetime
)engine innodb default charset utf8;

-- ②创建一个事件，每隔6秒钟向event_test_table表中插入数据
create event insert_event
on schedule every 6 second
do
-- begin
insert into event_test_table values(null,now());
-- end; # 只执行一条语句可以不用begin end;

select * from event_test_table;

# 三、查看事件
-- 查看所有事件的状态
show events;

# 四、事件调度器
# 事件是由事件调度器管理的，所以需要打开事件调度器才能执行事件
-- 1、查看事件调度器的状态
show variables like '%schedule%';

# 事
件调度器的状态是由全局变量event_scheduler来控制的
-- 2、打开事件调度器
set global event_scheduler = on;#通过设置全局变量event_scheduler的值为on开事件调度器
set global event_scheduler = 1; #也可以设置全局变量event_scheduler的值为1开事件调度器
-- 3、关闭事件调度器
set global event_scheduler = off;#通过设置全局变量event_scheduler的值为off来打开事件调度器
set global event_scheduler = 0;#也可以设置全局变量event_scheduler的值为0来打开事件调度器

-- 4、通过进程列表来查看事件调度器的状态
-- 查看进程列表
show processlist;
# 事件调度器开启之后是由一个进程来执行的，可以在进程列表中查看到

# 小练习1：创建一个事件每隔一分钟清空表数据
create event delete_event
on schedule every 1 minute
do
truncate table event_test_table;	# 清空表数据
# delete from event_test_table;	# 删除表中所有数据
# 一般用truncate清空表数据比较好，因为truncate的效率比delete高

-- 数据库中时间单位有：
# year年、month月、day天、week星期、hour小时、minute分钟、second秒钟、microsecond微秒

# 五、单独开启/关闭某个事件
-- 开启和关闭事件调度器会使所有的事件都同时开启或关闭，数据库也允许单个事件的开启或关闭
# 1、单独关闭某个事件
-- 基本格式：alter event 事件名 disable;
alter event insert_event disable;
# 2、单独打开某个事件
-- 基本格式：alter event 事件名 enable;
alter event insert_event enable;

# 事件调度器相当于一个事件的总开关，而每个事件都有一个自己独立的开关

# 小练习2：创建一个清空表事件，固定时间点清空表数据
create event delete2_event
on schedule at '2019-12-21 22:10:00' + INTERVAL 1 day	# AT 某个时间点执行事件
do
truncate table event_test_table;

create event delete3_event
on schedule at now() + INTERVAL 1 day	# AT 某个时间点执行事件
do
truncate table event_test_table;

# 小练习3：创建一个清空表事件，6天之后开启事件，每小时清空表，1个月后停止事件并不保留事件
create event delete4_event
on schedule every 1 hour
starts current_timestamp() + INTERVAL 6 day # current_timestamp() 获取当前时间，和now()类似
ends current_timestamp() + interval 1 month 
ON COMPLETION NOT PRESERVE # 停止事件之后不保留
do
truncate table event_test_table;

