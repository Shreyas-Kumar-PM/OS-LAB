#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

int main(){
	pid_t pid=fork();

	if(pid == -1){
		perror("Fork Failed");
		exit(1);
	}

	if(pid == 0){
		printf("Child Process:\n");
		printf("PID: %d\n",getpid());
		printf("PPID: %d\n",getppid());
	} else{
		printf("Parent Process:\n");
		printf("PID: %d\n",getpid());
		printf("PPID: %d\n",getppid());
	}

	return 0;
}

