#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void bubbleSort(char *arr[], int n){
	for(int i=0;i<n-1;i++){
		for(int j=0;j<n-i-1;j++){
			if(strcmp(arr[j],arr[j+1])>0){
				char *temp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
			}
		}
	}
}

void selectionSort(char *arr[],int n){
	for(int i=0;i<n-1;i++){
		int minIdx=i;
		for(int j=i+1;j<n;j++){
			if(strcmp(arr[j],arr[minIdx])<0){
				minIdx=j;
			}
		}
		char *temp=arr[i];
		arr[i]=arr[minIdx];
		arr[minIdx]=temp;
	}
}

int compareStrings(const void *a, const void *b){
	return strcmp(*(const char **)a,*(const char **)b);
}

void quickSort(char *arr[],int n){
	qsort(arr,n,sizeof(char *),compareStrings);
}

int main(){
	int N;
	printf("Enter the number of strings:");
	scanf("%d",&N);

	char *arr[N];
	printf("Enter %d strings:",N);
	for(int i=0;i<N;i++){
		arr[i]=malloc(100*sizeof(char));
		scanf("%s",arr[i]);
	}

	pid_t pid1=fork();
	if(pid1==-1){
		perror("fork failed");
		exit(1);
	}

	if(pid1==0){
		printf("\nChild 1 (Bubble Sort):\n");
		bubbleSort(arr,N);
		for(int i=0;i<N;i++){
			printf("%s\n",arr[i]);
		}
		exit(0);
	} else{
		pid_t pid2=fork();
		if(pid2==-1){
			perror("Fork failed");
			exit(1);
		}

		if(pid2==0){
			printf("\nChild 2(Quick Sort):\n");
			quickSort(arr,N);
			for(int i=0;i<N;i++){
				printf("%s\n",arr[i]);
			}
			exit(0);
		}else{
			int status;
			waitpid(pid1,&status,0);
			printf("\nParent Process: One of the child processes has terminated.\n");
		}
	}

	for(int i=0;i<N;i++){
		free(arr[i]);
	}
	return 0;
}

