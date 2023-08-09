/*
#include <stdio.h>
#define MAXSIZE 100001

int main(int argc,char *argv[]){
    int A, N, i, sum, remainder=0,len;
    char arr[MAXSIZE];
    scanf("%d %d", &A, &N);
    if(N==0){
        printf("0");
        return 0;
    }
    len=(A==9?N:N-1);
    for(i=0; i<N; i++)
    { 
        sum = A*(N-i)+remainder;
        arr[len-i] = sum%10+'0';
        remainder = sum/10;
    }
    if(remainder)
        arr[len-i] = remainder+'0';
	arr[len+1]='\0';
    printf("%s", arr);   
    return 0;
}
*/

#include <stdio.h>
#define MAXSIZE 100001

int main(int argc,char *argv[]){
    int A, N, i, sum, remainder=0;
    char arr[MAXSIZE];
    scanf("%d %d", &A, &N);
    if(N==0){
        printf("0");
        return 0;
    }
    for(i=0; i<N; i++)
    { 
        sum = A*(N-i)+remainder;
        arr[i] = sum%10;
        remainder = sum/10;
    }
    if(remainder)
        arr[i] = remainder;
	else
		i--;
	for(int j=i;j>=0;j--)
    	printf("%d", arr[j]);   
    return 0;
}


















/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 100000+1
int main(int argc,char*argv[])
{
	char arr[MAXSIZE];
	int A,N,i,j,k,len;
	int temp,help,temp2;
	scanf("%d %d",&A,&N);
	if(N==0) 
	{
		printf("0");
		return 0;
	}
	memset(arr,0,sizeof(char)*MAXSIZE);
	if(A==9)
	{
		arr[0]='0';
		for(i=1;i<=N;i++)
			arr[i]=A+'0';
		len=N;		
	}else
	{
		for(i=0;i<N;i++)
			arr[i]=A+'0';
		len=N-1;
	}
	for(j=N-1;j>=0;j--)
	{
		for(k=j-1;k>=0;k--)
		{
			temp=arr[len-k]-'0'+A;
			if(temp>9)
			{
				arr[len-k]=temp%10+'0';
				help=1;
				temp2=arr[len-k-help]-'0'+1;
				while(temp2>9)
				{
					arr[len-k-help]=temp2%10+'0';
					help++;
					temp2=arr[len-k-help]-'0'+1;
				}	
				arr[len-k-help]+=1;			
			}else
				arr[len-k]=temp+'0';
		}
	}
	for(int i=0;i<=len;i++)
		printf("%c",arr[i]);
	printf("\n");
	return 0;
}
*/
