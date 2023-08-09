#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class smallComparater
{
public:
    bool operator()(int o1, int o2)
    {
        return o1 < o2; //每次弹出最大的
    }
};

int lessMoney(int arr[], int sz)
{
    priority_queue<int, vector<int>, smallComparater> q;
    int currentSum = 0;
    for (int i = 0; i < sz; i++)
    {
        currentSum += arr[i];
        q.push(arr[i]);
    }
    int sum = 0, cur = 0;
    while (q.size() > 1)
    {
        sum += currentSum;
        cur = q.top();
        q.pop();
        currentSum = currentSum - cur;
    } 
    return sum;
}

int main()
{
    int arr[] = {10, 20, 30, 40};
    cout << lessMoney(arr, 2);
}