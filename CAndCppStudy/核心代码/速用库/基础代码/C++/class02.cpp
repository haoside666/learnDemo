/*
    继承的特点:
    有public, protected, private三种继承方式，它们相应地改变了基类成员的访问属性。
1.public 继承：基类 public 成员，protected 成员，private 成员的访问属性在派生类中分别变成：public, protected, private
2.protected 继承：基类 public 成员，protected 成员，private 成员的访问属性在派生类中分别变成：protected, protected, private
3.private 继承：基类 public 成员，protected 成员，private 成员的访问属性在派生类中分别变成：private, private, private

*/
#include <iostream>
using namespace std;

class A{
public:
    A(){id_public=1,id_protected=2;};
    A(int id1,int id2,int id3):id_public(id1),id_protected(id2),id_private(id3){}
public:
    int id_public;
protected:
    int id_protected;
private:
    int id_private;

};

class B:public A{
public:
    B(){id_public=11,id_protected=12;};
    void test(){
        cout<<"id_public:"<<id_public<<endl;
        cout<<"id_protected:"<<id_protected<<endl;
    }
};

class C:protected A{
public:
    C(){id_public=21,id_protected=22;};
    void test(){
        cout<<"id_public:"<<id_public<<endl;
        cout<<"id_protected:"<<id_protected<<endl;
    }

};
class C1:public C{
public:
    C1(){id_public=210,id_protected=220;};
    void test(){
        cout<<"id_public:"<<id_public<<endl;
        cout<<"id_protected:"<<id_protected<<endl;
    }

};

class D:private A{
public:
    D(){id_public=31,id_protected=32;};
    void test(){
        cout<<"id_public:"<<id_public<<endl;
        cout<<"id_protected:"<<id_protected<<endl;
    }

};
class D1:public D{
public:
    D1(){};
    void test(){
        // cout<<id_public<<endl;
        // cout<<id_protected<<endl;
        cout<<"啥也没有"<<endl;
    }

};

int main(int argc,char *argv[])
{
    A a(1,2,3);
    B b;
    C c;
    C1 c1;
    D d;
    D1 d1;
    cout<<"a.id_public:"<<a.id_public<<endl;
    cout<<"b.id_public:"<<b.id_public<<endl;
    cout<<"b.test()"<<endl;;
    b.test();
    cout<<"c.test()"<<endl;
    c.test();
    cout<<"c1.test()"<<endl;
    c1.test();
    cout<<"d.test()"<<endl;
    d.test();
    cout<<"d1.test()"<<endl;
    d1.test();

    return 0;
}