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

int main()
{
		printf("Enter 1 to give the signal\n");
		int n;
		scanf("%d",&n);
		key_t key=3000;
		int shmid=shmget(key,sizeof(int),IPC_CREAT|0666);
		int *pid=shmat(shmid,0,0);
		if(n==1)	
		{
			kill(*pid,SIGUSR1);
		}
}
	
