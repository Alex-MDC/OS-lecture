
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAX_LINE 100
#define MAX_COMS 100
#define clear() printf("\033[H\033[J")


/*
int readIn(char* str)
{
	char* buf;
	buf = readline("\n>>> ");
	if (strlen(buf) != 0) {
		add_history(buf);
		strcpy(str, buf);
		return 0;
	} 
	else
	{
		return 1;
	}
}
*/

void printDir()
{
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	printf("\n Dir: %s", cwd);
}

void runCommand(char** parsed)
{
	pid_t pid = fork();
	//forks a child 
	if (pid == -1) {
		printf("\n Error, failed forking child");
		return;
	}
	else if (pid == 0) {
		//inside child process
		if(execvp(parsed[0], parsed) <0) {
			printf ("\n Error, can't execute command" );
		}
		exit(0);
	} else {
		wait(NULL);
		//parent waitts for child to finish
		return;
	}
}

int specialCommand(char** parsed)
{
	int cmds = 2, i, sarg =0;
	char* cmdList[cmds];
	char* user;
	cmdList[0] = "exit";
	cmdList[1] = "cd";

	for (i =0; i<cmds; i++) {
		if (strcmp(parsed[0], cmdList[i]) == 0){
			sarg = i +1;
			break;
		}
	}
	switch (sarg){
		case 1:
			printf("\n Thanks for trying out TurtleShell! \n");
			exit(0);
		case 2:
			chdir(parsed[1]);
			return 1;
		default:
			break;
		}
	return 0;
}

void parseIn(char* str, char** parsed)
{
	int i;
	for (i=0; i<MAX_COMS; i++) {
		parsed[i] = strsep(&str, " ");
		if (parsed[i] == NULL)
			break;
		if (strlen(parsed[i]) ==0)
			i--;
	}
}

int processString(char* str, char** parsed)
{
	parseIn(str, parsed);
	
	if (specialCommand(parsed)) {
	return 0;
       	}
	else
	return 1;
}

int main() {
	char inputString[MAX_LINE], *parsedArgs[MAX_COMS];
	int execType = 0;
	while (1) {
	printDir();
	/*
	if(readIn(inputString)){
		continue;
	}
	*/
	execType = processString(inputString, parsedArgs);
	// returns 0 if there is no command or one ofe the special commands
	// 1 for parsed commands that aren't special (requires extra process)
	
	if(execType == 1)
		runCommand(parsedArgs);
	}
	return 0;
}



