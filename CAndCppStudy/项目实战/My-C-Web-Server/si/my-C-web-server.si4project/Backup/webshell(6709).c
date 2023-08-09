#include "wrap.h"
#include "parse.h"

int main(void) 
{
    char *command,content[MAXLINE];

    /* Extract the two arguments */
    command= getenv("QUERY_STRING");

    sprintf(content,"input command:%s\n",command);
    sprintf(content, "%sThanks for visiting!\r\n", content);
  
    /* Generate the HTTP response */
    printf("Content-length: %ld\r\n", strlen(content));
    printf("Content-type: text/html\r\n\r\n");
    printf("%s", content);
    fflush(stdout);
    exit(0);
}
