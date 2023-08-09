#include <iostream>
#include <string>
using namespace std;

struct student
{
    string name;
    int age;
    string sex;
    double score;
};

void printStuInfo(student &stu)
{
    cout<<"姓名:"<<stu.name<<endl;
    cout<<"年龄:"<<stu.age<<endl;
    cout<<"性别:"<<stu.sex<<endl;
    cout<<"成绩:"<<stu.score<<endl;
}
int main(int argc,char *argv[])
{
    student stu1;
    stu1.name="小明";
    stu1.age=18;
    stu1.sex="男";
    stu1.score=80.0;

    printStuInfo(stu1);
    return 0;
}