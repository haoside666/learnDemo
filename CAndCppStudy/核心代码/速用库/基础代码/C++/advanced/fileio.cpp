#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[])
{
    // char data[100];
    // // 以写模式打开文件
    // ofstream outfile;
    // outfile.open("afile.dat");
    // cout << "Writing to the file" << endl;
    // cout << "Enter your name: ";
    // cin.getline(data, 100);
    // // 向文件写入用户输入的数据
    // outfile << data << endl;
    // cout << "Enter your age: ";
    // cin >> data;
    // cin.ignore();
    // // 再次向文件写入用户输入的数据
    // outfile << data << endl;
    // // 关闭打开的文件
    // outfile.close();
    // // 以读模式打开文件
    // ifstream infile;
    // infile.open("afile.dat");
    // cout << "Reading from the file" << endl;
    // infile >> data;
    // // 在屏幕上写入数据
    // cout << data << endl;
    // // 再次从文件读取数据，并显示它
    // infile >> data;
    // cout << data << endl;
    // // 关闭打开的文件
    // infile.close();

    string data;
    fstream file;
    file.open("afile.dat", ios::in);
    cout << "Everything in the file :";
    while (1)
    {
        file >> data;
        if(file.eof()) break;  //注意eof函数放置的位置
        cout << data << endl;
    }
    file.close();
    file.open("afile.dat", ios::in);
    file.seekg(2, ios::beg);

    cout << "file.seekg(2,ios::beg) after :";
    while (1)
    {
        file >> data;
        if(file.eof()) break;
        cout << data << endl;
    }
    file.close();
    return 0;
}