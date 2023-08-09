#include "Alist.h"
extern int length;
extern int MAX;
void PrintHead(void)
{
	printf("-----------------------------------------\n");
}
void ListOne(STUMESSAGE list)
{
	printf("\t学号:%s\n", list.stuNO);
	printf("\t姓名:%s\n", list.name);
	printf("\t专业:%s\n", list.spec);
	printf("\t年级:%d\n", list.grade);
	printf("\t性别:%s\n", list.sex);
	printf("\t出生年月:%d-%d-%d\n", list.birthday.year, list.birthday.month,list.birthday.day);
}
void ListAll(STUMESSAGE stu[])
{	
	if (length == 0)
	{
		printf("系统中无数据!!!\n");
		return;
	}
	system("clear");
	int i = 0;	
	for (i = 0; i < length; i++)
	{
		PrintHead();
		printf("第%d条记录:\n",i+1);
		ListOne(stu[i]);
	}
	system("echo  Please press any key to continue\n");
	getchar();
}
void Append(STUMESSAGE stu[])
{
	while (1)
	{	
		char c,Con;
		STUMESSAGE temp;
		system("clear");
		printf("请输入一条添加学生信息的记录\n");
		printf("请输入学号(唯一primary key)(限十个数字):");
		scanf("%s", temp.stuNO);
		while(NumOfSear(stu, temp.stuNO) != -1)
		{		
			printf("输入错误,该学号已存在!!!\n");
			printf("请重新输入学号!\n");
			scanf("%s", temp.stuNO);
		}
		printf("请输入姓名(限四个汉字):\n");
		scanf("%s", temp.name);
		printf("请输入专业(限十个汉字):\n");
		scanf("%s", temp.spec);
		printf("请输入年级:(数字) 如大一输入1\n");
		scanf("%d", &temp.grade);
		printf("请输入性别(男或女) \n");
		scanf("%s", temp.sex);
		printf("请输入出生年月:(年月日之间以空格或回车隔开)如 2000 1 8\n");
		scanf("%d %d %d", &temp.birthday.year,&temp.birthday.month,&temp.birthday.day);
		stu[length++] = temp;
		printf("添加成功!!!\n");
		if (length== MAX)
		{
			MAX *= 2;
			stu = realloc(stu, sizeof(STUMESSAGE)*MAX);
		}
		while ((c = getchar()) != '\n' && c != EOF);
		printf("是否继续添加(Y or N):N--跳出\n");
		Con = userSelect();
		while (Con == EOF)
		{
			printf("输入错误,重新选择!!!\n");
			printf("是否继续添加(Y or N):N--跳出\n");
			Con = userSelect();
		}
		if (Con == 'n' || Con == 'N') break;
	}
}
