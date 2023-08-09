#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLENGTH 100
typedef char ElementType;
typedef struct SNode* Stack;
typedef enum{false,true} bool;
struct SNode
{
    ElementType data[MAXLENGTH];
    int top;
};
Stack init()
{
    Stack mystack=malloc(sizeof(struct SNode));
    mystack->top=0;
    mystack->data[0]='\0';//哨兵
}

void push(Stack mystack,ElementType data)
{
    mystack->data[++mystack->top]=data;
}

ElementType pop(Stack mystack)
{
    return mystack->data[mystack->top--];
}

char temp[9]="<>()[]{}";

int test(Stack mystack,ElementType data);
int main(int argc,char *argv[])
{
    char buf[MAXLENGTH];
    char arr[8][3]={"/*","*/","(",")","[","]","{","}"};
	char brr[9]="()[]{}/*";
    Stack mystack=init();
    int len,flags=0;
    char ch;
    while(1)
    {
        gets(buf);
        if(flags) break;
        len=strlen(buf);
        if(len==1&&(buf[0]=='.'||buf[0]=='\0')) break;
        for(int i=0;i<len;i++)
        {
			while(1)
			{
				for(int j=0;j<8;j++)
				{
					if(brr[j]==buf[i]) goto down;
				}
				if(i==len-1) break;
				i++;
			}
			down:
            if(buf[i]=='/'&&buf[i+1]=='*')
            {
                push(mystack,'<');
                i++;
            }
            else if(buf[i]=='*'&&buf[i+1]=='/')
            {
                flags=test(mystack,'<');
				i++;      
            }else
            switch(buf[i])
            {
                case '(':
                case '[':
                case '{':
                    push(mystack,buf[i]);
                    break;
                case ')':
                    flags=test(mystack,'(');
                    break;
                case ']':
                    flags=test(mystack,'[');
                    break;
                case '}':
                   flags=test(mystack,'{');
                   break;
            }
			if(flags) break;
        }
    }
    if(mystack->top==0)
        printf("YES");
    else
    {
        printf("NO\n");
		if(flags%2==0)
        	printf("?-%s",arr[flags-1]);
		else
			printf("%s-?",arr[flags-1]);
    }   
}
int test(Stack mystack,ElementType data)
{
	char ch=pop(mystack);
	if(ch==data)
		return 0;
	else
	{
		if(ch=='\0')
		{
			for(int i=0;i<8;i+=2)
			{
				if(data==temp[i])
					return i+2;
			}
		}
		for(int i=0;i<8;i+=2)
		{
			if(ch==temp[i])
				return i+1;
		}
	}
}
