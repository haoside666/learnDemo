#include "Alist.h"
int length = 0;//数组中存储的有效信息
int MAX = 200;//记录动态数组的最大长度
int main()
{
	STUMESSAGE* stu= (STUMESSAGE*)malloc(sizeof(STUMESSAGE)*MAX);//申请堆内存
	SysInfo();
	MenuOfMain(stu);
	Quit(stu);
	return 0;
}
void SysInfo(void)
{
	printf("这是XX小组的学籍管理系统!\n");
	printf("生成日期2019-11-22,版权所有归XX小组!!!\n");
	printf("提示:本系统录取或修改学生信息时要按要求输入,否则后果自负!\n");		
	system("echo  Please press any key to continue\n");
	getchar();		
}
void Menu()
{
	system("clear");
	printf("****************************************************\n");
	printf("****       欢迎使用XX版学生管理系统           ****\n");
	printf("****                 请选择                     ****\n");
	printf("****             0.退出系统                     ****\n");
	printf("****             1.录入学生信息	                ****\n");
	printf("****             2.修改学生信息	                ****\n");
	printf("****             3.删除学生信息	                ****\n");
	printf("****             4.查询学生信息	                ****\n");
	printf("****             5.输出学生信息	                ****\n");	
	printf("****             6.导出原有信息	                ****\n");
	printf("****             7.保存学生信息	                ****\n");
	printf("****             8.排序学生信息	                ****\n");
	printf("****************************************************\n");
}
void MenuOfMain(STUMESSAGE stu[])
{
	char choose;
	char ch;

	while (1)
	{			
		Menu();
		printf("请选择:");
		choose = userInput();
		if (choose == EOF|| choose<'0'|| choose>'9')
		{
			printf("非法输入,请重新选择--输入0-9的数字!!!\n");
			sleep(1);
			continue;
		}
		switch (choose)
		{
			//0.退出系统
		case '0':
			Quit(stu); 
			break;
			//录入学生信息
		case '1':
			Append(stu);
			break;
			//2.修改学生信息
		case '2':
			Modify(stu);
			break;
			//3.删除学生信息
		case '3':
			Delete(stu);
			break;
			//4.查询学生信息
		case '4':
			sleep(1);
			MenuOfSear(stu);
			break;
			//5.输出学生信息
		case '5':
			ListAll(stu);
			break;
			//读取原有数据
		case '6':
			ExportData(stu);
			break;
		case '7':
			//保存
			SaveData(stu);
			break;		
			//排序
		case '8':
			sleep(1);
			Sort(stu);
			break;
		}
		if ((choose == '1' || choose == '2' || choose == '3' || choose == '5') && length != 0||choose=='9')
			continue;
		printf("是否继续:(Y or N)--N退出系统\n");
		ch = userSelect();
		while (ch == EOF)
		{
			printf("输入错误,重新选择!!!\n");
			printf("是否继续:(Y or N)--N退出系统\n");
			ch = userSelect();
		}
		if (ch == 'N' || ch == 'n') break;
	}
}
void Quit(STUMESSAGE stu[])
{
	free(stu);
	system("clear");
	printf("退出系统中...\n");
	sleep(1);
	exit(0);
}
//文件读取与保存
void ExportData(STUMESSAGE stu[])
{	
	char *p;
	char ch;
	FILE*fp = fopen("student.xxx", "rb");
	if (fp == NULL)//如果文件不存在,则创建一个新的文件
	{
		printf("系统中无数据,读取将清空已有数据!!!\n");
		printf("(是否清除)Y or N:");
		ch = userSelect();
		while (ch == EOF)
		{
			printf("输入错误,重新选择!!!\n");
			printf("(是否清除)Y or N:");
			ch = userSelect();
		}
		if (ch == 'N' || ch == 'n') return;
		length = 0;
		memset(stu, 0, sizeof(STUMESSAGE)*MAX);
		fp=fopen("student.xxx", "wb");
		fclose(fp);		
		return;
	}
	fread(&length, sizeof(int), 1, fp);
	while(length > MAX)
	{
		MAX*= 2;
		stu = realloc(stu, sizeof(STUMESSAGE)*MAX);
	}
	fread(stu, sizeof(STUMESSAGE), length, fp);	
	for (p = (char*)(int)stu; p < (char*)(int)(stu + sizeof(STUMESSAGE)*length); p++)//解密
	{
		*p = *p ^ 8;
	}
	fclose(fp);
	printf("读取数据完毕!!!\n");
}
void SaveData(STUMESSAGE stu[])
{	
	int i = 0;
	char *p;
	char ch;
	if (length == 0)
	{		
		printf("系统中无数据!!!\n");
		printf("是否确定保存!!!(Y or N):\n");
		ch = userSelect();
		while (ch == EOF)
		{
			printf("输入错误,重新选择!!!\n");
			printf("是否确定保存!!!(Y or N):\n");
			ch = userSelect();
		} 
		if (ch == 'Y' || ch == 'y')
		{
			FILE*fp = fopen("student.xxx", "wb");
			fclose(fp);//清空文件
			printf("信息保存成功!!!\n");
		}		
		else
		{
			printf("信息取消保存!");
		}
		return;
	}	
	FILE*fp = fopen("student.xxx", "wb");
	fwrite(&length, sizeof(int), 1, fp);
	for (p = (char*)(int)stu; p < (char*)(int)(stu + sizeof(STUMESSAGE)*length); p++)//加密
	{
		*p = *p ^ 8;
	}
	fwrite(stu,sizeof(STUMESSAGE),length,fp);
	fclose(fp);
	printf("信息保存成功!!!\n");
}
//排序
void Sort(STUMESSAGE stu[])
{
	if (length == 0)
	{
		printf("系统中无数据,无法排序!!!\n");
		return;
	}
	while (1)
	{		
		char choose;		
		SortMenu();
		choose=userInput();
		if (choose == EOF||choose<'0'||choose>'2')
		{
			printf("非法输入,请重新选择--输入0-2的数字!!!\n");
			sleep(1);
			continue;
		}
		switch (choose)
		{
		case '0':
			break;
		case '1':
			qsort(stu, length, sizeof(STUMESSAGE), SortNum); 
			printf("排序成功!!!\n");
			printf("按任意键继续...\n");
			getchar();
			break;
		case '2':
			qsort(stu, length, sizeof(STUMESSAGE),SortGrade);
			printf("排序成功!!!\n");
			printf("按任意键继续...\n");
			getchar();
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
int SortGrade(const void* _stu1, const void* _stu2)
{
	STUMESSAGE*stu1 = (STUMESSAGE*)_stu1;
	STUMESSAGE*stu2 = (STUMESSAGE*)_stu2;
	return stu1->grade - stu2->grade;
}
int SortNum(const void* _stu1, const void* _stu2)
{
	STUMESSAGE*stu1 = (STUMESSAGE*)_stu1;
	STUMESSAGE*stu2 = (STUMESSAGE*)_stu2;
	return strcmp(stu1->stuNO, stu2->stuNO);
}
void SortMenu()
{
	system("clear");
	printf("************************************************\n");
	printf("****          欢迎使用信息排序功能          ****\n");
	printf("****                请选择                  ****\n");
	printf("****             0.返回主菜单               ****\n");
	printf("****             1.按学号排序               ****\n");
	printf("****             2.按年级排序               ****\n");
	printf("************************************************\n");
	printf("请选择:");
}
//用于界面选择功能时(数字)
char userInput()
{
	char arr[50];
	char choose;
	scanf("%s", arr);//防止用户输入其他无关字符所带来的影响	
	if (strlen(arr) > 1)
	{
		while ((choose = getchar()) != '\n' && choose != EOF);//清空缓存区
		return EOF;
	}
	getchar();
	return arr[0];
}
//用于界面选择是否时(Y or N)
char userSelect()
{
	char ch = userInput();
	if (ch == 'Y' || ch == 'y' || ch == 'N' || ch == 'n')
		return ch;
	else
		return EOF;
}
