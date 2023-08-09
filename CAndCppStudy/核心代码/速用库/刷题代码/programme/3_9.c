#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define For(i,a,b) for(i=a;i<=b;i++)
int main()
{
    int n,m,i;
	scanf("%d %d",&n,&m);
    For(i,0,n-1)
    {
        char c;
        int sz=0;
		char choose;
		while ((choose = getchar()) != '\n' && choose != EOF);
        while((c=getchar())!='\n')
        {
			if(c=='S')sz++;
            else sz--;
            if(sz<0||sz>m)
            {
                sz=-1;
                break;
            }         
        }
        if(sz) printf("NO");
        else printf("YES");

    }
    return 0;
}

