#include <iostream>
using namespace std;
#define maxSize 10

class DualStack{
public:
    int top[2];
    int buttom[2];
    int v[maxSize];
    void init()
    {
        buttom[0]=0;
        buttom[1]=maxSize-1;
        top[0]=0;
        top[1]=maxSize-1;
    }

    void push(int index,int data)
    {
        if(top[0]+1==top[1]){
            cout<<"栈满"<<endl;
            return;
        }
        //说明入前一个栈
        if(index==0)
        {
            v[top[0]++]=data;
        }else if(index==1){
            v[top[1]--]=data;
        }else cout<<"栈号输入错误!!!"<<endl;
    }

    int pop(int index)
    {
        if(index==0){
            if(top[0]==0){
                cout<<"栈空,无法弹出数据!!!"<<endl;
                return -1;
            }
            else{
                return v[--top[0]];
            }
        }else if(index==1){
            if(top[1]==maxSize-1){
                cout<<"栈空,无法弹出数据!!!"<<endl;
                return -1;
            }
            else{
                return v[++top[1]];
            }
        }else{
            cout<<"栈号输入错误!!!"<<endl;
            return -1;
        }
    }

    bool isEmpty()
    {
        return top[0]==0&&top[1]==maxSize-1;
    }
};

int main()
{
    DualStack sta;
    sta.init();
    sta.push(0,1);
    sta.push(1,99);
    sta.push(1,98);
    sta.push(0,2);
    cout<<sta.pop(0)<<endl;
    cout<<sta.pop(0)<<endl;
    cout<<sta.pop(1)<<endl;
    cout<<sta.pop(1)<<endl;
    cout<<boolalpha<<sta.isEmpty()<<endl;
    return 0;
}