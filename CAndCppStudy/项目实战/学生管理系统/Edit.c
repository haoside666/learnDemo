#include "Alist.h"
extern int length;
extern int MAX;
//修改学生信息
void Modify(STUMESSAGE stu[])
{
	if (length == 0)
	{
		printf("系统中无数据,无法修改!!!\n");
		return;
	}
	char id[11];	
	char ch;
	int index;
	STUMESSAGE temp;
	while (1)
	{
		system("clear");
		printf("请输入要修改学生的学号:\n");
		scanf("%s", id);
		getchar();
		index = NumOfSear(stu, id);
		if (index == -1)
		{
			printf("没有找到相应记录!!\n");
		}
		else
		{
			temp = stu[index];
			PrintHead();
			ListOne(stu[index]);		
			printf("1.只修改学号\n");
			printf("2.只修改姓名\n");
			printf("3.只修改专业\n");
			printf("4.只修改年级\n");
			printf("5.只修改性别\n");
			printf("6.只修改出生年月\n");
			printf("7.修改这条记录的全部信息\n");
			printf("请选择:");
			ch = userInput();
			while (ch == EOF||ch<'1'||ch>'7')
			{
				printf("输入错误,重新选择!!!\n");
				printf("请选择:");
				ch = userInput();
			} 
			switch (ch)
			{
			case '1':
				printf("请输入学号(唯一primary key)(限十个数字):");
				scanf("%s", temp.stuNO);
				break;
			case '2':
				printf("请输入姓名(限四个汉字):\n");
				scanf("%s", temp.name);
				break;
			case '3':
				printf("请输入专业(限十个汉字):\n");
				scanf("%s", temp.spec);
				break;
			case '4':
				printf("请输入年级:(数字) 如大一输入1\n");
				scanf("%d", &temp.grade);
				break;
			case '5':
				printf("请输入性别(男或女):\n");
				scanf("%s", temp.sex);
				break;
			case '6':
				printf("请输入出生年月:(年月日之间以空格或回车隔开)如 2000 1 8\n");
				scanf("%d %d %d", &temp.birthday.year, &temp.birthday.month, &temp.birthday.day);
				break;
			case '7':
				printf("请输入修改后学生的信息记录\n");
				printf("请输入学号(唯一primary key)(限十个数字):");
				scanf("%s", temp.stuNO);
				printf("请输入姓名(限四个汉字):\n");
				scanf("%s", temp.name);
				printf("请输入专业(限十个汉字):\n");
				scanf("%s", temp.spec);
				printf("请输入年级:(数字) 如大一输入1\n");
				scanf("%d", &temp.grade);
				printf("请输入性别(男或女):\n");
				scanf("%s", temp.sex);
				printf("请输入出生年月:(年月日之间以空格或回车隔开)如 2000 1 8\n");
				scanf("%d %d %d", &temp.birthday.year, &temp.birthday.month, &temp.birthday.day);				
				break;
			}
			stu[index] = temp;
			printf("修改成功!!!\n");
		}
		printf("是否继续修改(Y or N):N---跳出\n");
		ch=userSelect();
		while (ch == EOF)
		{
			printf("输入错误,重新选择!!!\n");
			printf("是否继续修改(Y or N):N---跳出\n");
			ch = userSelect();
		} 
		if (ch == 'N' || ch == 'n')
			break;
	}
}
//删除学生信息
void Delete(STUMESSAGE stu[])
{	
	char id[11];
	char ch;
	int index;
	while (1)
	{
		if (length == 0)
		{
			printf("系统中无数据,无法删除!!!\n");
			return;
		}
		system("clear");
		printf("请输入要删除学生的学号:\n");
		scanf("%s", id);
		getchar();
		index = NumOfSear(stu, id);
		if (index == -1)
		{
			printf("没有找到相应记录!!\n");
		}
		else
		{
			PrintHead();
			ListOne(stu[index]);
			printf("是否删除该条记录(Y or N):Y--删除\n");
			ch = userSelect();
			while (ch == EOF)
			{
				printf("输入错误,重新选择!!!\n");
				printf("是否继续:(Y or N)--N退出系统\n");
				ch = userSelect();
			} 
			if (ch == 'Y' || ch == 'y')
			{
				DelList(stu, index);
				length--;
				printf("删除成功!!!\n");
			}
			else if (ch == 'n' || ch == 'N')
			{
				printf("取消删除!!!\n");
			}
		}
		printf("是否继续删除(Y or N):N--跳出\n");
		ch = userSelect();
		while (ch == EOF)
		{
			printf("输入错误,重新选择!!!\n");
			printf("是否继续删除(Y or N):N--跳出\n");
			ch = userSelect();
		} 
		if (ch == 'N' || ch == 'n')
			break;
	}		
}
int DelList(STUMESSAGE stu[], int i)
{
	if (i == -1)return 0;
	int j;
	for (j = i; j <length-1; j++)
	{
		stu[j] = stu[j+1];
	}
	return 1;
}
//查询学生信息
void MenuOfSear(STUMESSAGE stu[])
{
	if (length == 0)
	{
		printf("系统中无数据,无法查询!!!\n");
		sleep(1);
		return;
	}
	while (1)
	{	
		char choose;
		
		childMenu();
		choose = userInput();
		if (choose == EOF || choose<'0' || choose>'2')
		{
			printf("非法输入,请重新选择--输入0-2的数字!!!\n");
			continue;
		}
		switch (choose)
		{
		case '0':
			break;
		case '1':
			SearNum(stu);
			break;
		case '2':
			SearGrade(stu);
			break;
		}
		if (choose == '0')
		{
			sleep(1);
			MenuOfMain(stu);
			break;
		}			
	}
}
void SearNum(STUMESSAGE stu[])
{
	system("cls");
	char id[11];
	int index;
	printf("请输入学号:\n");
	scanf("%s", id);
	getchar();
	index = NumOfSear(stu, id);
	if (index==-1 )
	{
		printf("没有找到相应记录!!\n");
	}
	else
	{
		PrintHead();
		ListOne(stu[index]);
	}
	printf("按任意键继续...\n");
	getchar();//按任意键继续
}
void SearGrade(STUMESSAGE stu[])
{
	int grade;
	int i,count = 0;
	system("clear");
	printf("请输入年级:(数字) 如大一输入1\n");
	scanf("%d", &grade);
	getchar();
	for (i = 0; i < length; ++i)
	{
		if (stu[i].grade==grade)
		{
			PrintHead();
			printf("第%d条记录\n", ++count);
			ListOne(stu[i]);			
		}
	}
	if (count > 0)
	{
		printf("共找到%d条记录!\n",count);
	}
	else
	{
		printf("没有找到相关记录\n");
	}
	printf("按任意键继续...\n");
	getchar();//按任意键继续
}
void childMenu()
{
	system("clear");
	printf("************************************************\n");
	printf("****          欢迎使用学生查询功能          ****\n");
	printf("****                请选择                  ****\n");
	printf("****             0.返回主菜单               ****\n");
	printf("****             1.按学号查询               ****\n");
	printf("****             2.按年级查询               ****\n");
	printf("************************************************\n");
	printf("请选择:");
}
int NumOfSear(STUMESSAGE stu[], char stuNum[])
{
	int i;
	for (i = 0; i < length; i++)
	{
		if (strcmp(stu[i].stuNO,stuNum)==0)
			return i;
	}
	return -1;
}
