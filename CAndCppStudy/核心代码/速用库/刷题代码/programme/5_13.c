#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define For(i,a,b) for(i=a;i<=b;i++)
#define Ref(i,a,b) for(i=a;i>=b;i--)
#define max(a,b) a>b?a:b
typedef struct A *Node;
struct A
{
    char c;
    Node child[37];
    int cnt;
};
char get(char c)
{
    if(c>='A'&&c<='Z') c=c-'A'+'a';
    if((c>='0'&&c<='9')||c=='_'||(c>='a'&&c<='z'))return c;
    return '?';
}
int getIndex(char c)
{
    if(c>='a'&&c<='z')return c-'a';
    if(c>='0'&&c<='9')return c-'0'+26;
    return 36;   
}
Node newNode(char c)
{
    Node res=malloc(sizeof(struct A));
    for(int i=0;i<37;i++)
        res->child[i]=NULL;
    res->cnt=0;
    res->c=c;
    return res;
}
int len=0;
int num=0;
void insert(Node root,char* word)
{
    Node cur=root;
    int l=0;
    while((*word)!='\0'&&l<15)
    {
        if(!(cur->child[getIndex(*word)]))
        {
            cur->child[getIndex(*word)]=newNode(*word);
        }
        cur= cur->child[getIndex(*word)];
        //printf("%c ",cur->c);
        word++;l++;
    }
    if(!cur->cnt)num++;
    cur->cnt++;
}
struct B
{
    char c[81];
    int cnt;
};
typedef struct B *wordSet;
void dfs(Node root,wordSet set,char word[],int deep)
{
    //printf("%c",root->c);
    if(deep!=-1)word[deep]=root->c;
    //if(!deep)printf("%c ",root->c);
    if(root->cnt)
    {
        word[deep+1]='\0';
        set[len].cnt=root->cnt;
        strcpy(set[len].c,word);len++;
        //printf("%s %d\n",word,deep);
	}
	for(int i=0;i<37;i++)
	{
		if(root->child[i])
       	dfs(root->child[i],set,word,deep+1);
	}
}
int cmp(const void* a,const void* b)
{
    wordSet c,d;
    c=(wordSet)a;d=(wordSet)b;
	if(c->cnt!=d->cnt)
    	return c->cnt>d->cnt;
	else
		return strcmp(d->c,c->c);
}
int main()
{
    char c;
    char tmp[80+1];
    char word[100];
    Node root=newNode('?');
	wordSet set;
    while(1)
    {
        int l=0;
        while(get(c=getchar())=='?')if(c=='#')goto end;tmp[l++]=get(c);
        while(get(c=getchar())!='?')tmp[l++]=get(c);tmp[l]='\0';
        //printf("%s\n",tmp);
        insert(root,tmp);
        if(c=='#')goto end;
    }
    end:
    set=malloc(sizeof(struct B)*num);
    dfs(root,set,word,-1);
    qsort(set,num,sizeof(struct B),cmp);
    int num2=num/10;
	printf("%d\n",num);
	for(int i=num-1;i>=num-num2;i--)
	{
		 printf("%d:%s\n",set[i].cnt,set[i].c);
	}
    return 0;
}


