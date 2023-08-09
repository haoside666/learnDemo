#include <stdio.h>
#include <string.h>
#define MAXSIZE 21
typedef struct node
{
    char ch;
    int grade;
}NODE;
int main(int argc,char *argv[])
{
    char buf[MAXSIZE];
    NODE stack[MAXSIZE],temp;
    int top=0,len,i=0,flags=0;
    gets(buf);
    len=strlen(buf);
    stack[top].grade=-1;
	
	if(buf[i]=='-')
	{
		printf("-");
		i++;
	}
	else if(buf[i]=='+')
	{
		printf(" ");
		i++;
	}	
	if(buf[i]>='0'&&buf[i]<='9')
	{
		flags=1;
		while((buf[i]>='0'&&buf[i]<='9')||buf[i]=='.')
		{
			printf("%c",buf[i++]);
		}
	}
    while(i<len)
    {
		if(buf[i]>='0'&&buf[i]<='9')
		{
			if(flags)
				printf(" ");
			else
				flags=1;
			while((buf[i]>='0'&&buf[i]<='9')||buf[i]=='.')
			{
				printf("%c",buf[i++]);
			}
			continue;
		}
		switch(buf[i])
		{
			case '+':
			case '-':
				temp.grade=1;
				while(stack[top].grade>=temp.grade)
				{
				   printf(" %c",stack[top--].ch);
				}
				temp.ch=buf[i];
				stack[++top]=temp;
				i++;
				break;
			case '*':
			case '/':
				temp.grade=2;
				while(stack[top].grade>=temp.grade)
				{
				   printf(" %c",stack[top--].ch);
				}
				temp.ch=buf[i];
				stack[++top]=temp;
				i++;
				break;
			case '(':
				temp.grade=0;
			    temp.ch=buf[i];
			    stack[++top]=temp;
				i++;
				if(buf[i]=='-'||buf[i]=='+')
				{			
					if(buf[i]=='-')
						printf(" -");
					else 
						printf(" ");
					i++;
					while((buf[i]>='0'&&buf[i]<='9')||buf[i]=='.')
					{
						printf("%c",buf[i++]);
					}
					break;
				}
				break;
			case ')':
				while(stack[top].ch!='(')
			    {
			        printf(" %c",stack[top--].ch);
			    }
			    top--;
				i++;
				break;        
	    }
    }
	while(top!=0)
	{
		printf(" %c",stack[top--].ch);
	}
    return 0;
}
