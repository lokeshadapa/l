#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <signal.h>
#include <sys/shm.h>
#include <poll.h>
char res[100][100];
int *pid,*pid1;
int m=0;
int ffd;
int k;
char buffer1[256];

void flush(char * buf)
{
    for(int i=0;buf[i]!='\0';i++)
    buf[i]='\0';
}
void handler(int signo)
{
	if(signo==SIGUSR1)
	{
		signal(SIGUSR1,handler);
		int j;
		for(j=0;j<m;j++)
		strcat(buffer1,res[j]);
		printf("%s\n",buffer1);
		write(ffd,buffer1,256);
		kill(*pid1,10);
	}
}

int main(int argc,char *argv[])
{
	mkfifo("s",0666);
	mkfifo("fifos",0666);
	ffd=open("s",O_RDWR);
	int fd[2];
	char buffer[100];
	pipe(fd);
	int p,i=0;
	p=fork();
	signal(SIGUSR1,handler);
	if(p==0)
	{
		close(fd[0]);
		write(fd[1],"pipe",5);
	}
	else
	{
		close(fd[1]);
		key_t key=3000;
		key_t key1=5000;
		int shmid=shmget(key,sizeof(int),IPC_CREAT|0666);
		pid=(int *)shmat(shmid,0,0);
		*pid=getpid();
		int shmid1=shmget(key1,sizeof(int),IPC_CREAT|0666);
		pid1=(int *)shmat(shmid1,0,0);
		FILE *fp=popen("./h","r");
		int pofd=fileno(fp);
		struct pollfd pfd[4];
		pfd[0].fd=0;
		pfd[1].fd=fd[0];
		pfd[2].fd=open("fifos",O_RDWR);
		pfd[3].fd=pofd;
		pfd[0].events=POLLIN;
		pfd[1].events=POLLIN;
		pfd[2].events=POLLIN;
		pfd[3].events=POLLIN;
		while(1)
		{
			flush(buffer);
			while(poll(pfd,4,0)<=0) {};
			if(pfd[0].revents & POLLIN)
			{
				scanf("%s",&buffer);
				strcpy(res[m++],buffer);
			}
			if(pfd[1].revents & POLLIN)
			{
				read(fd[0],buffer,100);
				strcpy(res[m++],buffer);
			}
			if(pfd[2].revents & POLLIN)
			{
				read(pfd[2].fd,buffer,100);
				strcpy(res[m++],buffer);
			}
			if(pfd[3].revents & POLLIN)
			{
				read(pfd[3].fd,buffer,100);
				strcpy(res[m++],buffer);
			}
		}
	}
}
