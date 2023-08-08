
create database if not exists examsys;

use examsys;

DROP TABLE IF EXISTS `test`;

create table test(
id int primary key,
type int not null,
commitId int,
CmdArgv varchar(500),
addition varchar(50)
)engine innodb default charset utf8;



insert into test values
(1,1,1,' 123 ','123'),
(2,1,1,' 456','456'),
(3,1,2,'12','12'),
(4,2,1,'34','34'),
(5,2,1,'',''),
(6,1,3,' 1','2'),
(7,3,1,'2 ','3'),
(8,4,1,'',''),
(9,3,2,'',''),
(10,1,4,'4',''),
(11,4,2,'4',''),
(12,3,2,'',''),
(13,3,3,'6',''),
(14,4,2,'3',''),
(15,4,3,'6',''),
(16,1,5,' 78 ',''),
(17,2,2,'',''),
(18,2,2,'',''),
(19,2,3,'',''),
(20,2,3,'','');




