#include <iostream>
#include <string>
#include <stack>
using namespace std;

bool correct(string exp)
{
    stack<char> sta;
    char temp,c;
    for(int i=0;i<exp.size();i++)
    {
        if(exp[i]=='('||exp[i]=='['||exp[i]=='{')
            sta.push(exp[i]);
        else{
            if(sta.empty())
            {
               return false; 
            }
            temp=sta.top();
            sta.pop();
            switch (exp[i])
            {
            case ')':
                c='(';
                break;
            case ']':
                c='[';
                break;
            case '}':
                c='{';
                break;
            }
            if(c!=temp){
                return false;
            }
        }
    }
    return sta.empty();
}


int main(int argc,char *argv[])
{
    string testStr="[]{}()[";
    cout<<boolalpha<<correct(testStr)<<endl;

    testStr="[][]((()))";
    correct(testStr);
    cout<<boolalpha<<correct(testStr)<<endl;
    testStr="][]((()))";
    cout<<boolalpha<<correct(testStr)<<endl;
    return 0;
}