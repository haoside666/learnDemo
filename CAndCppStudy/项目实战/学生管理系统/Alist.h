/*
*	头文件:放类型定义,函数声明,包含需要用到的库文件
*/
#ifndef ALIST_H//防止头文件重复包含
#define ALIST_H

#define _CRT_SECURE_NO_WARNINGS
//库文件包含
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//类型定义
typedef struct Date
{
	int year;//年
	int month;//月
	int day;  //日
}MYDATE;
typedef struct StuMessage
{
	char stuNO[11];//学号
	char name[9];//姓名
	char spec[21];//专业
	int grade;//年级
	char sex[5];//性别
	MYDATE birthday;//出生日期
}STUMESSAGE;

//函数声明
//Main.c
//函数功能:在屏幕上输出系统版权信息并等待用户响应
void SysInfo(void);
//主菜单
void Menu();
//函数功能:在屏幕上显示主菜单,接受用户并相应用户相应操作
void MenuOfMain(STUMESSAGE stu[]);
//函数功能:退出菜单系统,并调用exit(0)系统函数结束程序运行
void Quit(STUMESSAGE stu[]);
//函数功能:导出文件中原有数据
void ExportData(STUMESSAGE stu[]);
//函数功能:保存数据到文件中
void SaveData(STUMESSAGE stu[]);
//函数功能:排序数据界面
void Sort(STUMESSAGE stu[]);
//函数功能:按照年级进行排序
int SortGrade(const void* _stu1, const void* _stu2);
//函数功能:按照学号进行排序
int SortNum(const void* _stu1, const void* _stu2);
//函数功能:排序子主菜单
void SortMenu();
//函数功能:用于在界面选择功能时解决用户随便选择所带来的影响(数字)
char userInput();
//函数功能:用于在界面选择是否时解决用户随便选择所带来的影响(Y or N)
char userSelect();

//List.c
//函数功能: 在屏幕上显示输出列表的表头。
void PrintHead(void);
//函数功能: 在屏幕上以行的方式显示输出一个学生的相关信息 
void ListOne(STUMESSAGE list);
//函数功能:在屏幕上以列表方式输出所有学生的信息,调用PrintHead()输出表头,在调用ListOne()函数逐一输出各条记录
void ListAll(STUMESSAGE stu[]);
//函数功能:录入一条学生记录到记录数组的末尾
void Append(STUMESSAGE stu[]);


//Edit.c
//函数功能:通过输入学号查询学生的相应记录信息,如果存在在屏幕上输出相应学生记录并通过重新输入的方法修改学生的记录,否则输出没有找到相关记录
void Modify(STUMESSAGE stu[]);
//函数功能:通过输入学号查询学生的相应记录信息,如果存在在屏幕上输出相应学生记录,用户确定删除后调用DelList()函数将其删除,否则输出没有找到相关记录
void Delete(STUMESSAGE stu[]);
//函数功能: 如果数组中存在下标为i的记录，删除该记录并返回1,否则返回0
int DelList(STUMESSAGE stu[], int i);
//函数功能:在屏幕上显示查询子主菜单,接收用户选择并响应用户操作
void MenuOfSear(STUMESSAGE stu[]);
//函数功能:通过输入学号调用NumOfsear()函数查询学生的相应记录信息,如果存在调用PrinHead()函数和ListOne()函数在屏幕上输出相应学生记录,否则输出没有找到相应记录
void SearNum(STUMESSAGE stu[]);
//函数功能: 通过输入年级查询学生的相应记录信息，如果存在在屏幕以列表方式输出相应学生记录，并输出统计满足条件的学生个数，否则输出没有找到相关记录。
void SearGrade(STUMESSAGE stu[]);
//函数功能: 根据接收到的学生学号，在相应记录数组中进行查询，如果存在相应记录，返加相应的数组下标, 否则返回-1。
int NumOfSear(STUMESSAGE stu[], char stuNum[]);
//查询子主菜单
void childMenu();
#endif
