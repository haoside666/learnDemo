#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>
int main(int argc,char *argv[])
{
/*
1 000 000 -
1 010 000 软链接
1 100 000 s
0 110 000 b
0 100 000 d
0 010 000 设备
0 001 000 管道
*/
	struct stat fileinode;
	struct passwd *passwd;
	struct group *group;
	int arr[16];
	char brr[8]="pcdb-ls";
	int k=15;
	memset(arr,0,16);
	if(argc<2)
	{
		printf("./app filename\n");
		exit(EXIT_FAILURE);
	}
	stat(argv[1],&fileinode);
	passwd = getpwuid(fileinode.st_uid);
	group = getgrgid(fileinode.st_gid);
	printf("%d\n",fileinode.st_mode);
	while(fileinode.st_mode!=0)
	{
		arr[k--]=fileinode.st_mode%2;
		fileinode.st_mode/=2;		
	}
	for(int i=0;i<16;i++)
		printf("%d",arr[i]);
	printf("\n");
	int sum=arr[0]*8+arr[1]*4+arr[2]*2+arr[3];
	printf("%c",brr[sum/2]);
	for(int i=7;i<16;i++)
	{
		if(arr[i]==0) printf("-");
		else{
			switch(i%3)
			{
				case 0: printf("x"); break;
				case 1:	printf("r"); break;
				case 2:	printf("w"); break;
			}
		}		
	}
	printf(" ");
	printf("%ld ",fileinode.st_nlink);
	printf("%s ",passwd->pw_name);
	printf("%s ",group->gr_name);
	printf("%ld\n",fileinode.st_size);

	
	return 0;
}
