

create database if not exists dockerfile_study default charset utf8 collate utf8_general_ci;

use dockerfile_study;

DROP TABLE IF EXISTS `gitChange`;
create table gitChange(
pAddress varchar(100) not null,
rAddress varchar(120) not null,
newCommitID int not null,
newCommit varchar(40) not null,
oldCommitID int not null,
oldCommit varchar(40) not null,
mType varchar(10) not null,
cmd varchar(20) not null,
cmdArgv varchar(500) not null,
addition varchar(100),
commitNum int
)engine innodb default charset utf8;



