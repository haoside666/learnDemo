#include <iostream>
#include <string>
using namespace std;


class Test{
public:
	Test();
	Test(int a,int b);
	~Test();
	Test(const Test& other);
	Test operator+(const Test &other); 
	friend Test operator+(const Test t1, Test t2); 
	friend ostream& operator<<(ostream& os,const Test &a);
private:
	int a;
	int b;
};

Test::Test(){
	a=b=0;
}

Test::Test(int a,int b)
{
	this->a=a;
	this->b=b;
}
Test::~Test()
{

}

Test::Test(const Test&other)
{
	a=other.a;
	b=other.b;
}

Test Test::operator+(const Test &other)
{
	this->a=this->a+other.a;
	this->b=this->b+other.b;
} 
Test operator+(Test t1, Test t2)
{
	t1.a=t1.a+t2.a;
	t1.b=t1.b+t2.b;
	return t1;
}

ostream& operator<<(ostream& os,const Test &t)
{
	cout<<"a="<<t.a<<" , b="<<t.b<<endl;
}


int main(int argc,char *argv[])
{
	Test t(1,2);
	Test t1(t);
	cout<<t;
	cout<<t1;
	return 0;
}
