/*
重载运算符与重载函数

*/

#include <iostream>
using namespace std;

class A{
public:
    A(){};
    A(int num):num(num){};
    A operator=(const A& other){
        this->num=other.num;
    }
    //无序写法
    A operator+(A& other);
    friend A operator+(const int num, const A& other); 
    A operator ++();//前缀自增
    A operator ++(int);//后缀自增，参数需要加int
    //输入输出
    friend istream& operator>>(istream& in,A&a);
    friend ostream& operator<<(ostream& os,const A&a);
    //  ()运算符
    A operator()(int a, int b, int c){
        A temp;
        temp.num=this->num+a+b+c;
        return temp;
    }
     //  ()运算符
    int operator[](int index){
        return index;
    };
    //关系运算符
    friend bool operator==(const A&a1,const A&a2); 
private:
    int num;
};
//前缀自增
A A::operator++(){
    this->num++;
    return *this;
}

//后缀自增
A A::operator++(int)
{
    A temp;
    temp.num=this->num;
    this->num++;
    return temp; 
}

//加法无序
A A::operator+(A& other){
    A temp;
    temp.num=other.num+this->num;
    return temp;
};

//加法有序
A operator+(const int num, const A& other){
    A temp;
    temp.num=other.num+num;
    return temp;    
}; 
//输入重载
istream& operator>>(istream& in,A&a)
{
    in>>a.num;
    return in;
}
//输出重载
ostream& operator<<(ostream& os,const A&a)
{
    os<<a.num;
    return os;
}

//关系运算符
bool operator==(const A&a1,const A&a2)
{
    return a1.num==a2.num;
}
int main(int argc,char *argv[])
{
    // A a1(1);
    // A a2(2);
    // A a3;
    // A a4(4);
    // A a5,a6;
    // a3=a1+a2;
    // cout<<a3<<endl;
    // a5=a4++;
    // cout<<a4<<endl;
    // cout<<a5<<endl;
    // a6=++a4;
    // cout<<a4<<endl;
    // cout<<a6<<endl;

    // A a;
    // cin>>a;
    // cout<<a;

    // A a(2);
    // A a1;
    // a1=100+a;
    // cout<<a1<<endl;

    // A a(666);
    // A a1;
    // a1=a(1,2,3);
    // cout<<a1<<endl;   

    // A a(555);
    // cout<<a[666]<<endl;

    A a1(333);
    A a2(333);
    bool flags=a1==a2;
    cout<<"a1==a2:"<<boolalpha<<flags<<endl;
    return 0;
}