dockerfile指令参考：https://github.com/moby/buildkit/blob/master/frontend/dockerfile/docs/reference.md

## FROM

```
三种格式:
FROM [--platform=<platform>] <image> [AS <name>]
FROM [--platform=<platform>] <image>[:<tag>] [AS <name>]
FROM [--platform=<platform>] <image>[@<digest>] [AS <name>]


保留长度:
	所有
	
sql处理:
	select cmd,cmdArgv,count(*) into OUTFILE '/var/lib/mysql-files/output_from.csv' 
FIELDS TERMINATED BY ',' 
ENCLOSED BY ''
LINES TERMINATED BY '\n'
from gitChange_real where cmd='FROM' group by cmdArgv;

查询后结束处理过程:
过滤阶段
1.过滤含有'$'或'{'或'}'的行
2.过滤不含有@且含有:数量大于1的行
处理阶段
1.去除前缀--platform=<platform>
2.不含有@且不含有:的行,加上latest
3.去除as以及之后别名
4.相同的image+版本合并

```

## RUN

```
两种格式:
RUN <command> 
RUN ["executable", "param1", "param2"]


保留长度:
	三位
	
sql处理
	create view gitChange_newArgv as SELECT *,SUBSTRING_INDEX(REPLACE(REPLACE(cmdArgv, '\t', ''), '&&', ''), ' ', 3) AS new_argv FROM gitChange_real where cmd='RUN';
	
	select cmd,new_argv,count(*) into OUTFILE '/var/lib/mysql-files/output_run.csv' FIELDS TERMINATED BY ',' 
ENCLOSED BY ''
LINES TERMINATED BY '\n'
from gitChange_newArgv group by new_argv;
	
查询后结束处理过程
过滤阶段
1.过滤含有'$'或'{'或'}'或'['或']'或'('或')'的行
2.过滤注释行
3.过滤双引号、单引号、反引号为单数的行
4.过滤不含有字母的行

处理阶段(数据分为四类,第一类变量以-开头的参数，第二类a=b形式,第三类主要是命令，第四类主要是依赖项还有一些未知数据)
①.将双引号、单引号、反引号为双数的行，引号内的空格换成'___'==>即replace(' ', '___')
②.将结尾词为\\或\或;的行，结尾词去掉
③.
	1.以-开头的为参数，级别为0
	2.key=value形式为变量赋值，级别为1，检查key和value形式
	3.其余默认为命令，级别为2
	4.含有"<"或"?"或"Microsoft"以及以.tar、.zip、.txt、.conf、.deb、.jar、.js、.so、.dll为后缀的，级别为3
	切分内容，并得到每一个切片的类型，如果后一个切片的类型低于前一个切片，设置该位置为终止位置
	如[0 1 2 2]则终止位置为3，[0] [1] [2 2]三个片段，分别存入类型0，1，2数组中
	对于级别0，过滤只含有-的；对于级别1，检查key和value形式；对于级别2，类型进行二次分类，在分别存入分类号数组中去；对于级别3，直接存入数组
	

提取阶段
主要linux发行版
1.Alpine(基于Alpine linux系统)--apk
2.Ubuntu(基于Debian系统)--apt、dpkg
3.centos、amazonlinux、oraclelinux(基于Red Hat Enterprise Linux(RHEL)系统) --yum
4.fedora(基于Fedora系统)--dnf
5.opensuse(基于suse linux系统，社区版)--zypper
6.archlinux(基于Arch linux系统)--pacman

一.提取上诉所有发行版镜像/bin/目录下的所有可执行文件，得到共有命令列表和单个发行版剩余命令列表.
二.对于sql查询后的数据，匹配是否在列表中，在列表中，保留在RUN-split3.txt中
三.
	统计软件包安装命令占所有命令的比重，以及所有命令中出现频率最高的前五项
	只考虑软件包安装命令，统计七种软件包安装命令的占比
	考虑网络下载工具curl、wget命令的占比


软件包安装命令介绍
1.apk：Alpine Linux的包管理工具，用于安装、卸载、升级和查询软件包。apk命令是Alpine的命令行界面，可以通过简单的命令语法来执行包管理操作。例如，安装软件包可以使用apk add <package-name>命令。
2.dpkg：Debian和Ubuntu系列的Linux发行版的包管理工具，用于安装、卸载、升级和查询软件包。dpkg命令是一个命令行工具，可以直接使用dpkg命令来安装、卸载和管理软件包。例如，安装软件包可以使用dpkg -i <package-name>.deb命令。
3.apt或apt-get：APT（Advanced Package Tool）是一个用于Debian和Ubuntu系列的Linux发行版的包管理工具，提供了更高级的包管理功能。apt命令可以通过apt-get install <package-name>来安装软件包，也可以使用其他选项来管理软件包。
4.yum：Red Hat和CentOS系列的Linux发行版的包管理工具，用于安装、卸载、升级和查询软件包。yum命令是一个命令行工具，可以通过yum install <package-name>来安装软件包，也可以使用其他选项来管理软件包。
5.dnf：Dandified YUM（或称为dnf）是Red Hat和CentOS系列的Linux发行版的下一代包管理工具，是一个在Fedora及其衍生版（如CentOS Stream和Rocky Linux）中使用的包管理工具,用于安装、卸载、升级和查询软件包。dnf命令可以通过dnf install <package-name>来安装软件包，也可以使用其他选项来管理软件包。
6.zypper：SUSE Linux Enterprise Server（SLES）和openSUSE的包管理工具，用于安装、卸载、升级和查询软件包。zypper命令可以通过zypper install <package-name>来安装软件包，也可以使用其他选项来管理软件包。
7.pacman：Arch Linux的包管理工具，用于安装、卸载、升级和查询软件包。pacman命令可以通过pacman -S <package-name>来安装软件包，也可以使用其他选项来管理软件包。

```

## CMD

```
三种形式:
CMD ["executable","param1","param2"] (执行形式，这是首选形式）
CMD ["param1","param2"]（作为入口点的默认参数)
CMD command param1 param2 (shell形式）

保留长度:
	所有
	
sql处理:
	select cmd,cmdArgv,count(*) into OUTFILE '/var/lib/mysql-files/output_cmd.csv' 
FIELDS TERMINATED BY ',' 
ENCLOSED BY ''
LINES TERMINATED BY '\n'
from gitChange_real where cmd='CMD' group by cmdArgv;

查询后结束处理过程:
过滤阶段
1.过滤含有'$'的行
2.过滤[和]数量不相等的行
处理阶段
1.对于执行形式，去除结尾词的\
2.对于shell形式
	先将双引号、单引号、反引号为双数的行，引号内的空格换成'___'==>即replace(' ', '___')
	按空格切片
	'___'换回空格，调整每一个切片元素的格式
	转化为执行形式
3.合并同类项，排序
```

## LABEL

```
一种形式:
LABEL <key>=<value> <key>=<value> <key>=<value> ...）

保留长度:
	所有
	
sql处理:
	select cmd,cmdArgv,count(*) into OUTFILE '/var/lib/mysql-files/output_label.csv' 
FIELDS TERMINATED BY ',' 
ENCLOSED BY ''
LINES TERMINATED BY '\n'
from gitChange_real where cmd='LABEL' group by cmdArgv;

查询后结束处理过程:
过滤阶段
1.过滤含有'$'的行
处理阶段
1.去掉所有"、'、\
2.合并同类项，排序
统计信息
1.key=value出现最高的频率
2.只考虑key合并key,key出现最高的频率
```

## MAINTAINER

```
一种形式:
MAINTAINER <name>

保留长度:
	所有
	
sql处理:
	select cmd,cmdArgv,count(*) into OUTFILE '/var/lib/mysql-files/output_maintainer.csv' 
FIELDS TERMINATED BY ',' 
ENCLOSED BY ''
LINES TERMINATED BY '\n'
from gitChange_real where cmd='MAINTAINER' group by cmdArgv;

查询后结束处理过程:
同上
```

## EXPOSE

```
一种形式:
EXPOSE <port> [<port>/<protocol>...]

保留长度:
	所有
	
sql处理:
	select cmd,cmdArgv,count(*) into OUTFILE '/var/lib/mysql-files/output_expose.csv' 
FIELDS TERMINATED BY ',' 
ENCLOSED BY ''
LINES TERMINATED BY '\n'
from gitChange_real where cmd='EXPOSE' group by cmdArgv;

查询后结束处理过程:
过滤阶段
1.过滤含有'$'的行

处理阶段
1.去除/udp和/tcp
2.按空格切片，过滤得到列表中不为数字的元素
3.合并同类项，排序
```

## ENV

```
两种形式:
ENV <key>=<value> ...
ENV MY_VAR my-value


保留长度:
	所有
	
sql处理:
	select cmd,cmdArgv,count(*) into OUTFILE '/var/lib/mysql-files/output_env.csv' 
FIELDS TERMINATED BY ',' 
ENCLOSED BY ''
LINES TERMINATED BY '\n'
from gitChange_real where cmd='ENV' group by cmdArgv;

查询后结束处理过程:
过滤阶段
1.过滤含有'$'的行

处理阶段
1.预处理，除去结尾符，并将双引号、单引号、反引号为双数的行，引号内的空格换成'___'==>即replace(' ', '___')
2.按空格切片，对于没有=的形式，如果出现单数情况丢弃，将没有=的形式转换为=形式
3.检查每一个切片的a=b形式，保留正确的切片
4.合并同类项，排序
```

## ADD

```
两种形式:
ADD [--chown=<user>:<group>] [--chmod=<perms>] [--checksum=<checksum>] <src>... <dest>
ADD [--chown=<user>:<group>] [--chmod=<perms>] ["<src>",... "<dest>"]

保留长度:
	所有
	
sql处理:
	select cmd,cmdArgv,count(*) into OUTFILE '/var/lib/mysql-files/output_add.csv' 
FIELDS TERMINATED BY ',' 
ENCLOSED BY ''
LINES TERMINATED BY '\n'
from gitChange_real where cmd='ADD' group by cmdArgv;

查询后结束处理过程:
过滤阶段
1.过滤含有'$'的行

处理阶段
1.去除--chown=，--chmod=,--checksum=
2.合并同类项，排序
```

## COPY

```
两种形式:
COPY [--chown=<user>:<group>] [--chmod=<perms>] <src>... <dest>
COPY [--chown=<user>:<group>] [--chmod=<perms>] ["<src>",... "<dest>"]
保留长度:
	所有
	
sql处理:
	select cmd,cmdArgv,count(*) into OUTFILE '/var/lib/mysql-files/output_copy.csv' 
FIELDS TERMINATED BY ',' 
ENCLOSED BY ''
LINES TERMINATED BY '\n'
from gitChange_real where cmd='COPY' group by cmdArgv;

查询后结束处理过程:
过滤阶段
1.过滤含有'$'的行

处理阶段
1.去除--chown=，--chmod=,--from=,--link
2.合并同类项，排序
```

## ENTRYPOINT

```
两种形式:
ENTRYPOINT ["executable", "param1", "param2"]
ENTRYPOINT command param1 param2
保留长度:
	所有
	
sql处理:
	select cmd,cmdArgv,count(*) into OUTFILE '/var/lib/mysql-files/output_entrypoint.csv' 
FIELDS TERMINATED BY ',' 
ENCLOSED BY ''
LINES TERMINATED BY '\n'
from gitChange_real where cmd='ENTRYPOINT' group by cmdArgv;

查询后结束处理过程:
同CMD
```

## VOLUME

```
两种形式:
VOLUME ["/data"]
VOLUME /var/log /var/db

保留长度:
	所有
	
sql处理:
	select cmd,cmdArgv,count(*) into OUTFILE '/var/lib/mysql-files/output_volume.csv' 
FIELDS TERMINATED BY ',' 
ENCLOSED BY ''
LINES TERMINATED BY '\n'
from gitChange_real where cmd='VOLUME' group by cmdArgv;

查询后结束处理过程:
同CMD
```

## USER

```
两种形式:
USER <user>[:<group>]
USER <UID>[:<GID>]

保留长度:
	所有
	
sql处理:
	select cmd,cmdArgv,count(*) into OUTFILE '/var/lib/mysql-files/output_user.csv' 
FIELDS TERMINATED BY ',' 
ENCLOSED BY ''
LINES TERMINATED BY '\n'
from gitChange_real where cmd='USER' group by cmdArgv;

查询后结束处理过程:
过滤阶段
1.过滤含有'$'的行

处理阶段
1.去除结尾符\\
2.只保留user和uid
3.合并同类项，排序
```

## WORKDIR

```
一种形式:
WORKDIR /path/to/workdir

保留长度:
	所有
	
sql处理:
	select cmd,cmdArgv,count(*) into OUTFILE '/var/lib/mysql-files/output_workdir.csv' 
FIELDS TERMINATED BY ',' 
ENCLOSED BY ''
LINES TERMINATED BY '\n'
from gitChange_real where cmd='WORKDIR' group by cmdArgv;

查询后结束处理过程:
过滤阶段
1.过滤含有'$'的行

处理阶段
1.去掉所有"、'、[、]
2.如果长度大于1结尾有/，去除
3.合并同类项，排序
```

## ARG

```
一种形式:
ARG <name>[=<default value>]

保留长度:
	所有
	
sql处理:
	select cmd,cmdArgv,count(*) into OUTFILE '/var/lib/mysql-files/output_arg.csv' 
FIELDS TERMINATED BY ',' 
ENCLOSED BY ''
LINES TERMINATED BY '\n'
from gitChange_real where cmd='ARG' group by cmdArgv;

查询后结束处理过程:
过滤阶段
1.过滤含有'$'的行

处理阶段
1.去掉所有"、'
2.a b形式变为a=b,检查a=b形式
3.合并同类项，排序

提取阶段
1.判断value是否有小数点，有则认为是版本信息，拆分保留到ARG-split1.txt中
2.判断value是否为网站地址，拆分保留到ARG-split2.txt中
3.剩下的保留到ARG-split3.txt中

```

## ONBUILD

```
一种形式:
ONBUILD <INSTRUCTION>

保留长度:
	所有
	
sql处理:
	select cmd,cmdArgv,count(*) into OUTFILE '/var/lib/mysql-files/output_onbuild.csv' 
FIELDS TERMINATED BY ',' 
ENCLOSED BY ''
LINES TERMINATED BY '\n'
from gitChange_real where cmd='ONBUILD' group by cmdArgv;

过滤阶段
1.过滤含有'$'的行

处理阶段
1.去掉结尾符以及行最后的&&
2.合并同类项，排序
```

## STOPSIGNAL

```
一种形式:
STOPSIGNAL signal

保留长度:
	所有
	
sql处理:
	select cmd,cmdArgv,count(*) into OUTFILE '/var/lib/mysql-files/output_stopsignal.csv' 
FIELDS TERMINATED BY ',' 
ENCLOSED BY ''
LINES TERMINATED BY '\n'
from gitChange_real where cmd='STOPSIGNAL' group by cmdArgv;

查询后结束处理过程:
无

```

## HEALTHCHECK

```
两种形式:
HEALTHCHECK [OPTIONS] CMD command
HEALTHCHECK NONE

之前可以显示的选项包括
--interval=DURATION（默认值：30s)
--timeout=DURATION（默认值：30s)
--start-period=DURATION（默认值：0s)
--start-interval=DURATION（默认值：5s)
--retries=N

保留长度:
	所有
	
sql处理:
	select cmd,cmdArgv,count(*) into OUTFILE '/var/lib/mysql-files/output_healthcheck.csv' FIELDS TERMINATED BY ',' ENCLOSED BY '' LINES TERMINATED BY '\n' from gitChange_real where cmd='HEALTHCHECK' group by cmdArgv;

过滤阶段
1.过滤不含有CMD的行(即只分析第一种形式)

处理阶段
1.去掉--interval=DURATION、--timeout=DURATION、--start-period=DURATION、--start-interval=DURATION、--retries=N
2.合并同类项，排序

```

## SHELL

```
两种形式:
SHELL ["executable", "parameters"]
SHELL param1 param2 (shell形式）
保留长度:
	所有
	
sql处理:
	select cmd,cmdArgv,count(*) into OUTFILE '/var/lib/mysql-files/output_shell.csv'
FIELDS TERMINATED BY ','
ENCLOSED BY '' 
LINES TERMINATED BY '\n' 
from gitChange_real where cmd='SHELL' group by cmdArgv;

查询后结束处理过程:
同CMD

```

## 总的shell脚本

```
create view gitChange_newArgv as SELECT *,SUBSTRING_INDEX(REPLACE(REPLACE(cmdArgv, '\t', ''), '&&', ''), ' ', 3) AS new_argv FROM gitChange_real where cmd='RUN';


select cmd,cmdArgv,count(*) into OUTFILE '/var/lib/mysql-files/output_from.csv' FIELDS TERMINATED BY ',' ENCLOSED BY '' LINES TERMINATED BY '\n' from gitChange_real where cmd='FROM' group by cmdArgv;

select cmd,new_argv,count(*) into OUTFILE '/var/lib/mysql-files/output_run.csv' FIELDS TERMINATED BY ',' ENCLOSED BY '' LINES TERMINATED BY '\n' from gitChange_newArgv group by new_argv;

select cmd,cmdArgv,count(*) into OUTFILE '/var/lib/mysql-files/output_cmd.csv' FIELDS TERMINATED BY ',' ENCLOSED BY '' LINES TERMINATED BY '\n' from gitChange_real where cmd='CMD' group by cmdArgv;

select cmd,cmdArgv,count(*) into OUTFILE '/var/lib/mysql-files/output_label.csv' FIELDS TERMINATED BY ',' ENCLOSED BY '' LINES TERMINATED BY '\n' from gitChange_real where cmd='LABEL' group by cmdArgv;

select cmd,cmdArgv,count(*) into OUTFILE '/var/lib/mysql-files/output_maintainer.csv' FIELDS TERMINATED BY ',' ENCLOSED BY '' LINES TERMINATED BY '\n' from gitChange_real where cmd='MAINTAINER' group by cmdArgv;

select cmd,cmdArgv,count(*) into OUTFILE '/var/lib/mysql-files/output_expose.csv' FIELDS TERMINATED BY ',' ENCLOSED BY '' LINES TERMINATED BY '\n' from gitChange_real where cmd='EXPOSE' group by cmdArgv;

select cmd,cmdArgv,count(*) into OUTFILE '/var/lib/mysql-files/output_env.csv' FIELDS TERMINATED BY ',' ENCLOSED BY '' LINES TERMINATED BY '\n' from gitChange_real where cmd='ENV' group by cmdArgv;

select cmd,cmdArgv,count(*) into OUTFILE '/var/lib/mysql-files/output_add.csv' FIELDS TERMINATED BY ',' ENCLOSED BY '' LINES TERMINATED BY '\n' from gitChange_real where cmd='ADD' group by cmdArgv;

select cmd,cmdArgv,count(*) into OUTFILE '/var/lib/mysql-files/output_copy.csv' FIELDS TERMINATED BY ',' ENCLOSED BY '' LINES TERMINATED BY '\n' from gitChange_real where cmd='COPY' group by cmdArgv;

select cmd,cmdArgv,count(*) into OUTFILE '/var/lib/mysql-files/output_entrypoint.csv' FIELDS TERMINATED BY ',' ENCLOSED BY '' LINES TERMINATED BY '\n' from gitChange_real where cmd='ENTRYPOINT' group by cmdArgv;

select cmd,cmdArgv,count(*) into OUTFILE '/var/lib/mysql-files/output_volume.csv' FIELDS TERMINATED BY ',' ENCLOSED BY '' LINES TERMINATED BY '\n' from gitChange_real where cmd='VOLUME' group by cmdArgv;

select cmd,cmdArgv,count(*) into OUTFILE '/var/lib/mysql-files/output_user.csv' FIELDS TERMINATED BY ',' ENCLOSED BY '' LINES TERMINATED BY '\n' from gitChange_real where cmd='USER' group by cmdArgv;

select cmd,cmdArgv,count(*) into OUTFILE '/var/lib/mysql-files/output_workdir.csv' FIELDS TERMINATED BY ',' ENCLOSED BY '' LINES TERMINATED BY '\n' from gitChange_real where cmd='WORKDIR' group by cmdArgv;

select cmd,cmdArgv,count(*) into OUTFILE '/var/lib/mysql-files/output_arg.csv' FIELDS TERMINATED BY ',' ENCLOSED BY '' LINES TERMINATED BY '\n' from gitChange_real where cmd='ARG' group by cmdArgv;

select cmd,cmdArgv,count(*) into OUTFILE '/var/lib/mysql-files/output_onbuild.csv' FIELDS TERMINATED BY ',' ENCLOSED BY '' LINES TERMINATED BY '\n' from gitChange_real where cmd='ONBUILD' group by cmdArgv;

select cmd,cmdArgv,count(*) into OUTFILE '/var/lib/mysql-files/output_stopsignal.csv' FIELDS TERMINATED BY ',' ENCLOSED BY '' LINES TERMINATED BY '\n' from gitChange_real where cmd='STOPSIGNAL' group by cmdArgv;

select cmd,cmdArgv,count(*) into OUTFILE '/var/lib/mysql-files/output_healthcheck.csv' FIELDS TERMINATED BY ',' ENCLOSED BY '' LINES TERMINATED BY '\n' from gitChange_real where cmd='HEALTHCHECK' group by cmdArgv;

select cmd,cmdArgv,count(*) into OUTFILE '/var/lib/mysql-files/output_shell.csv' FIELDS TERMINATED BY ',' ENCLOSED BY '' LINES TERMINATED BY '\n' from gitChange_real where cmd='SHELL' group by cmdArgv;

```

