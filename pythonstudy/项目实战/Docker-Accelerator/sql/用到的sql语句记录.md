## gitChange

### 获取每个存储库中存入表中的commit数

```
	create view gitChange_real as select * from gitChange where cmd!="None";
	
	select pAddress,count(distinct newcommitId) from gitChange_real group by pAddress;
	
或者（下面这个更快）
	create view V_S_real as select pAddress,count(*) as num from gitChange_real group by pAddress,newCommitID;
	
	select pAddress,count(num) from V_S_real group by pAddress;
```

### 去除cmdArgv字段空格

```
update gitChange set cmdArgv=TRIM(cmdArgv);
```

### 更新cmd

```
update gitChange set cmd='None' where cmdArgv='' or cmdArgv like '#%';
```

### 删除特定条件数据

```
delete from gitChange where pAddress='https://github.com/h2non/imaginary.git';
```



## 常用查询语句

```
select * from dockerhubChange where cmdArgv like '/bin/bash%';

以name为分组统计同name下cmd的个数
select name,count(ditinct cmd) from dockerhubChange group by name;

以name为分组统计同name下cmd的个数（即记录数）
select name,count(cmd) from dockerhubChange group by name;

```





