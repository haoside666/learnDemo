#include <stdio.h>
#include "common.h"
int main(int argc,char *argv[])
{
	printf("4+5=%d\n",add(4,5));
	printf("4+5=%d\n",sub(4,5));
	printf("4*5=%d\n",mul(4,5));
	printf("4/5=%d\n",dive(4,5));
	return 0;
}
