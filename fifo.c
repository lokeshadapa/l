#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>

int main(int argc,char *argv[])
{
	mkfifo("fifos",0666);
	int fd;
	fd=open("fifos",O_RDWR);
	write(fd,"fifo",10);
}

