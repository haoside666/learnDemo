#include "./printlog.h"

int main(int argc,char *argv[])
{
	int i=1;
	PrintfLog("%d",i);
	DBG_FPRINT("%d",i);
	DBG_FPRINT("helloworld\n");
	return 0;
}
