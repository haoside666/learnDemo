//线性表实例01
/*
    ①.用数组实现线性表
    ②.完成最基本的增删改查的操作
    ③.用C++
*/

#include <iostream>
using namespace std;
#define MAXSIZE 100
using ElemType=int;
using Position=int;
    
class MyList{
public:
    MyList(){last=-1;}
    ~MyList(){}
    friend ostream& operator<<(ostream& os,const MyList &list);
    //采用尾插法
    void insertData(ElemType data);
    void daleteData(Position index);
    void updateData(Position index,ElemType data);
    ElemType findData(Position index);
private:
    ElemType data[MAXSIZE];
    Position last; /* 保存线性表中最后一个元素的位置 */
};
ostream& operator<<(ostream& os,const MyList &list)
{
    if(list.last==-1){
        cout<<"线性表为空"<<endl;
        return os;
    }
    cout<<"线性表的长度为:"<<list.last+1<<endl;
    cout<<"------------------------------\n元素为:";
    for (size_t i = 0; i <=list.last; i++)
    {
        cout<<list.data[i];
        if((i+1)%10==0)
        {
            cout<<endl;
        }else{
            cout<<" ";
        }
    }
    cout<<"\n------------------------------"<<endl<<endl;
    return os;
}

void MyList::insertData(ElemType data)
{
    this->last++;
    this->data[this->last]=data;
}

void MyList::daleteData(Position index)
{
    if(index<0||index>MAXSIZE||index>this->last)
    {
        cout<<"下标不存在"<<endl;
    }else
    {
        for (size_t i = index; i <this->last; i++)
        {
            this->data[i]=this->data[i+1];
        }
        this->last--;
    }

}
    
void MyList::updateData(Position index,ElemType data)
{
    if(index<0||index>MAXSIZE||index>this->last)
    {
        cout<<"下标不存在"<<endl;
    }else
    {
        this->data[index]=data;
    }
}

ElemType MyList::findData(Position index)
{
    if(index<0||index>MAXSIZE||index>this->last)
    {
        cout<<"元素不存在"<<endl;
    }else
    {
        return this->data[index];
    }
}

int main(int argc,char*argv[])
{
    MyList list;
    list.insertData(1);
    list.insertData(2);
    list.insertData(3);
    cout<<list;
    list.updateData(2,666);
    list.daleteData(1);
    cout<<list;
    cout<<"找查下标为1的元素为:"<<list.findData(1)<<endl;
    return 0;
}
