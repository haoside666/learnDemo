/*
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
int main(int argc,char*argv[])
{
	int fd=open("456",O_WRONLY|O_CREAT|O_TRUNC,0666); //fd=3
	int save_fd=dup(STDOUT_FILENO);
	dup2(fd,STDOUT_FILENO);
	close(fd);
	printf("hello\n");
	dup2(save_fd,STDOUT_FILENO);
	printf("world\n");
	close(save_fd);
	return 0;
}
*/

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void)
{
	int fd, save_fd;
	char msg[] = "This is a test\n";
	fd = open("somefile", O_RDWR|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);
	save_fd = open("tempfile", O_RDWR|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);
	if(fd<0) {
		perror("open");
		exit(1);
	}
	dup2(STDOUT_FILENO,save_fd);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	printf("hello\n");
	fflush(stdout);
	dup2(save_fd, STDOUT_FILENO);
	//write(STDOUT_FILENO, msg, strlen(msg));
	printf("%s",msg);
	close(save_fd);


	return 0;
}

/*
#include <stdio.h>
#include <unistd.h>

int main()
{
   int tfd = -1;

   tfd = dup(STDOUT_FILENO);
   //printf("itfd is %d\n", tfd);
   close(STDOUT_FILENO);
   printf("aaaaaaaaaaaaaaaaaa\n");
   fflush(stdout);
   dup2(tfd, STDOUT_FILENO);
   close(tfd);

   printf("bbbbbb\n");

   return 0;
}
*/
