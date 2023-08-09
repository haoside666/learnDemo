#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 4096
int main(int argc,char *argv[])
{
	int start,len,i=0,k=0,k1=0,sum=0;
	char buf[SIZE];
	char number[15];
	int num[SIZE];
	char symbol[SIZE];
	fgets(buf,SIZE,stdin);
	while(buf[i]!='=')
	{
		if(buf[i]>='0'&&buf[i]<='9')
		{
			start=i;
			while((buf[i]>='0'&&buf[i]<='9')&&buf[i]!='=')
			{
				i++;
			}
			len=i-start;
			memcpy(number,&buf[start],len);
			number[len]='\0';	
			num[k++]=atoi(number);		
			continue;
		}
		else if(buf[i]=='+'||buf[i]=='-'||buf[i]=='*'||buf[i]=='/')
		{
			symbol[k1++]=buf[i];
		}else
        {
            fprintf(stderr,"ERROR\n");
			exit(1);
        }
		i++;
	}
	sum=num[0];
	for(int j=0;j<k1;j++)
	{
		switch(symbol[j])
		{
			case '+': sum+=num[j+1];break;
			case '-': sum-=num[j+1];break;
			case '*': sum*=num[j+1];break;
			case '/': 
				if(num[j+1]==0)
				{
					fprintf(stderr,"ERROR\n");
					exit(0);
				}
				sum/=num[j+1];
				break;
		}
	}
	printf("%d\n",sum);
	return 0;
}
