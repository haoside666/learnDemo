/*
    多态
*/

#include <iostream>
#include <string>

using namespace std;


class Animal{
public:
    Animal(){}
    Animal(string name,string food):name(name),food(food){}
    virtual void voice(){cout<<"动物吃食物"<<endl;}; 
public:
    string name;
    string food;
};
class dog:public Animal{
public:
    dog(string name,string food):Animal(name,food){}
    void voice(){
        cout<<name<<"吃"<<food<<endl;
    }
};
class cat:public Animal{
public:
    cat(string name,string food):Animal(name,food){}
    void voice(){
        cout<<name<<"吃"<<food<<endl;
    }
};
int main(int argc,char *argv[])
{
    Animal* animal=new Animal();
    animal->voice();
    Animal* animal01=new dog("狗","骨头");
    animal01->voice();
    Animal* animal02=new cat("猫","鱼");
    animal02->voice();
    return 0;
}