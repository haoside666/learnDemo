#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 128
typedef struct SNode *Stack;
struct SNode{
	char data[MAXSIZE];
	int top;
};
Stack creat()
{
	Stack mystack=(Stack)malloc(sizeof(struct SNode));
	mystack->top=0;
	mystack->data[0]='\0';
	return mystack;	
} 
void push(Stack mystack,char data)
{
	mystack->data[++mystack->top]=data;	
} 

int main()
{
	int i,k=0,j;
	char ch1[MAXSIZE],ch2[MAXSIZE],ch[MAXSIZE];
	Stack mystack=creat();
	ch1[0]='\0';
	ch1['(']=')';
	ch1['{']='}';
	ch1['[']=']';
	ch1['<']='>';

	while(1)
	{
		gets(ch);
		if(ch[0]=='.'&&ch[1]=='\0') break;
		for(j=0;ch[j]!='\0';j++)
		{
			if(ch[j]=='('||ch[j]==')'||ch[j]=='['||ch[j]==']'||ch[j]=='{'||ch[j]=='}')
			{
				ch2[k++]=ch[j];
			}
			else if(ch[j]=='/'&&ch[j+1]=='*')
			{
				ch2[k++]='<';
				j++;
			}
			else if(ch[j]=='*'&&ch[j+1]=='/')
			{
				ch2[k++]='>';
				j++;
			}
		}
	}
	int flags=1;
	for(i=0;i<k;i++)
	{
		if(ch2[i]=='('||ch2[i]=='['||ch2[i]=='{'||ch2[i]=='<')
		{
			push(mystack,ch2[i]);
		}
		else if(ch2[i]==')'||ch2[i]==']'||ch2[i]=='}'||ch2[i]=='>')
		{
			if(ch1[mystack->data[mystack->top]]==ch2[i])
			{
				 mystack->top--;
			}
			else 
			{
				printf("NO\n");
				if(mystack->top==0)
				{
					if(ch2[i]==')') printf("?-)");
					else if(ch2[i]=='}') printf("?-}");
					else if(ch2[i]==']') printf("?-]");
					else if(ch2[i]=='>') printf("?-*/"); 
				}
				else
				{
					if(mystack->data[mystack->top]=='(') printf("(-?");
					else if(mystack->data[mystack->top]=='[') printf("[-?");
					else if(mystack->data[mystack->top]=='{') printf("{-?");
					else if(mystack->data[mystack->top]=='<') printf("/*-?");
				}
				flags=0;
				break;
			}
		}
	}
	if(flags==1)
	{
		if(mystack->top==0) printf("YES");
		else if(mystack->top!=0)
		{
		    printf("NO\n");
		    if( mystack->data[mystack->top]=='(') printf("(-?");
			else if( mystack->data[mystack->top]=='[') printf("[-?");
			else if( mystack->data[mystack->top]=='{') printf("{-?");
			else if( mystack->data[mystack->top]=='<') printf("/*-?");
		}
	}
	return 0;
}

