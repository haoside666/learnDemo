#include <sys/types.h>          
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <sys/un.h>
#include <unistd.h>
#include <errno.h>
#define SA struct sockaddr
#define UNIXSTR_PATH  "/tmp/msg.txt"
