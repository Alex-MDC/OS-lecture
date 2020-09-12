
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

//exit not working

#define MAX_LINE 700
#define MAX_ARG 100

#define STDIN 0
#define STDOUT 1


int main() {
	char* path= "/bin/";
	char progpath[30];
	char* args[MAX_ARG];
	char line[MAX_LINE];

	int execType;
	while (1) {
	char *username = getenv("USER");
	printf("\033[32m");
	printf("%s\n", username);
	printf("\033[36m\n");
	read(STDIN,line, MAX_LINE);
	if (strcmp (line, "exit") ==0 ){
	printf("exit was typed\n");
	break;
	}
	size_t length = strlen(line);
	if(line[length - 1] == '\n'){
	line[length - 1] = '\0';
	}

	char *token;
	token = strtok(line," ");
	int i =0;
	while(token != NULL) {
		args[i] = token;
		if (args[i] == "exit")
		{
			printf("exit detected\n");
			break;
		}
		token = strtok(NULL," ");

		i++;
	}
	args[i]=NULL;
	for(int k=0;k<i;k++)
	{
		if(args[k] =="cd"){
			chdir(args[k+1]);
		}
	}
	int argNum =i;
	/*
	for(i=0; i<argNum; i++){
		printf("%s\n", args[i]);
	}
	*/
	strcpy(progpath,path);
	strcat(progpath, args[0]);

	for(i=0; i<strlen(progpath); i++){
		if(progpath[i]=='\n'){
			progpath[i]='\0';
		}
	}



	pid_t pid; 
	pid = fork();
	if (pid < 0 ) {
		fprintf(stderr, "Error, could not fork\n");
		return 1;
	}
	else if (pid == 0) { 
		//in child process
		execvp(progpath,args);
		}
		else {
		//in parent
		wait(NULL);
		}
	}


	return 0;
}









