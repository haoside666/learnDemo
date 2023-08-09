#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(int argc,char **argv)
{
    string s;
    s="hello";
    string s1=" world##";
    cout<<s+s1<<endl;
    cout<<s.append(s1)<<endl;
    s.erase();
    // for(auto v:s)
    // {
    //     cout<<v<<endl;
    // }
    vector<int> vec={1,2,3,4,5,6,7,8,9};
    for(auto v=vec.begin();v!=vec.end();v++)
    {
        cout<<*v<<" ";
    }
    cout<<endl;
    for(int i=0;i<vec.size();i++)
    {
        cout<<vec.at(i)<<" ";
    }
    cout<<endl;
    return 0;    
}
