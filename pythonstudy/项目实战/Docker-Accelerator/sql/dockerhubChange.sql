

create database if not exists dockerfile_study default charset utf8 collate utf8_general_ci;

use dockerfile_study;

DROP TABLE IF EXISTS `dockerhubChange`;
create table dockerhubChange(
name varchar(30) not null,
newTagID int not null,
newTag varchar(50) not null,
oldTagID int not null,
oldTag varchar(50) not null,
mType varchar(10) not null,
cmd varchar(20) not null,
cmdArgv varchar(500) not null,
addition varchar(100),
changeNum int not null
)engine innodb default charset utf8;



