#include <iostream>
using namespace std;

typedef struct student
{
    string id;
    double score;
}stu;

void inputInfo(stu s[],int len)
{
    for(int i=0;i<len;i++)
    {
        cin>>s[i].id>>s[i].score;
    }
}

void sort(stu s[],int len)
{
    stu temp;
    int i;
    for(i=0;i<len-1;i++)
    {
        for(int j=len-1;j>i;j--)
        {
            if(s[j].score>s[j-1].score)
            {
                temp=s[j];
                s[j]=s[j-1];
                s[j-1]=temp;
            }
        }
        cout<<s[i].id<<"  "<<s[i].score<<"  ";
    }
    cout<<s[i].id<<"  "<<s[i].score<<"  ";
}

ostream& operator<<(ostream &os,const stu s[])
{
    for(int i=0;i<5;i++)
    {
        os<<s[i].id<<"  "<<s[i].score<<"  ";
    }
    os<<endl;
    return os;
}
int main(int argc,char *argv[])
{
    stu s[5];
    // inputInfo(s,5);
    s[0].id="1";s[0].score=12;
    s[1].id="2";s[1].score=90;
    s[2].id="3";s[2].score=68;
    s[3].id="4";s[3].score=88;
    s[4].id="5";s[4].score=27;
    cout<<s;
    sort(s,5);
    // cout<<s;
    return 0;
}