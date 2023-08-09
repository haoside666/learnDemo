#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct number
{
    int arr[1000000];
    int length;
} num1, num2,num3;
void initarr(void *arr,int val,int length)
{
    int *_arr=(int*)arr;
    for(int i=0;i<length;i++)
    {
        _arr[i]=val;
    }
}
void calcmul(int j)
{
    int i,n;
    initarr(num3.arr, -1, 10000);
    for(n=0;n<num2.length;n++)
    {
        num3.arr[n]=num2.arr[n]*j+(num3.arr[n]==-1?0:num3.arr[n]);
        if(num3.arr[n]>9)
        {
            num3.arr[n+1]=num3.arr[n]/10;
            num3.arr[n]=num3.arr[n]%10;
        }  
    }
    while(num3.arr[n]>9)
    {
        num3.arr[n+1]=num3.arr[n]/10;
        num3.arr[n]=num3.arr[n]%10;       
        n++;
    }  
    for(i=0;num3.arr[i]!=-1;i++);
    num3.length=i;
    memcpy(&num2,&num3,sizeof(struct number));
}
void calcfactorial(int i)
{
    initarr(num3.arr, -1, 10000);
    for (int j = 1; j <= i; j++)
    {
        if (j == 1)
        {
            num2.arr[0] = 1;
            num2.length = 1;
        }
        else
        {
            calcmul(j);
        }
    }
}
void calcsum()
{
    int n;
    for(n=0;n<num2.length;n++)
    {
        num1.arr[n]=(num1.arr[n]+num2.arr[n])%10;
        num1.arr[n+1]=(num1.arr[n]+num2.arr[n])/10+num1.arr[n+1];
    }
    while(num1.arr[n]>9)
    {
        num1.arr[n+1]=num1.arr[n]/10;
        num1.arr[n]=num1.arr[n]%10;   
        n++;
    }  
}
void print(struct number *num)
{
    for(int i=num->length-1;i>=0;i--)
    {
        printf("%d",num->arr[i]);
    }
    printf("\n");
}
int main(int argc,char*argv[])
{
    int n;
    if(argc!=2)
    {
        n=20;
    }else
    {
        n=atoi(argv[1]);
    }
    
    int i;
    initarr(num1.arr, 0, 10000);
    for (i = 1; i <= n; i++)
    {
        calcfactorial(i);
        printf("%d!=",i);
        print(&num2);
        //calcsum();
    }/*
    for (i = 1; i <= n; i++)
    {
        if(i==n)
            printf("%d!=",i);
        else
            printf("%d!+",i);  
    }
    */
    //print(&num1);
    printf("\n");
    return 0;
}