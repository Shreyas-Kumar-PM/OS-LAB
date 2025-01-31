#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int compareStrings(const void *a, const void *b){
	return strcmp(*(const char **)a, *(const char **)b);
}

int main(int argc,char *argv[]){
	if(argc < 2){
		printf("Usage: %s <string1> <string2> ... <stringN>\n", argv[0]);
		return 1;
	}

	pid_t pid=fork();

	if(pid == -1){
		perror("Fork Failed");
		return 1;
	}

	if(pid ==0){
		char **strings=malloc((argc -1)* sizeof(char *));
		for(int i=1;i<argc;i++){
			strings[i-1]=argv[i];
		}

		qsort(strings, argc -1, sizeof(char *), compareStrings);

		printf("Child Process (Sorted Strings):\n");
		for(int i=0;i<argc-1;i++){
			printf("%s\n",strings[i]);
		}

		free(strings);
		exit(0);
	} else{

		printf("\nParent Process (Unsorted Strings):\n");
		for(int i=1;i<argc;i++){
			printf("%s\n",argv[i]);
		}
	}

	return 0;
}

