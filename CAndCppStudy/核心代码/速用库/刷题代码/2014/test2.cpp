#include <stdio.h>

int calcequalAlphalength(char b[])
{
	int num=0,temp=0;
	for(int i=0;b[i]!=0;i++)
	{
		if(i==0)
		{
			temp=1;
		}else if(b[i-1]==b[i]){
			temp++;
		}else{
			if(temp>num)
			{
				num=temp;
			}
			temp=1;
		}
					
	}
	if(temp>num)
	{
		num=temp;
	}
	return num;
}

int main()
{
	char s[]="";
	printf("%d\n",calcequalAlphalength(s));
    char s1[]="acccac";
    printf("%d\n",calcequalAlphalength(s1));
    char s2[]="a";
    printf("%d\n",calcequalAlphalength(s2));
    char s3[]="acccacddddddddddddddddddddddd";
    printf("%d\n",calcequalAlphalength(s3));
}