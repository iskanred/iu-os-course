#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdbool.h>

#define COMMAND_BUFFER_SIZE 1001
#define ARGS_BUFFER_SIZE 21
#define WS " " // whitespace
#define AMPRSND "&" // ampersand


/* Split command string into an array of command arguments and returns number of arguments */
int splitCommand(char command[COMMAND_BUFFER_SIZE], char *commandArgs[ARGS_BUFFER_SIZE]) {
    char* token = strtok(command, WS); // first argument of the command (= name of program to be executed)
    int i = 0; // index of an argument

    /* go through all command arguments */
    while (token != NULL) {
        commandArgs[i] = token;  
        token = strtok(NULL, WS); // get next argument
        ++i;
    }

    commandArgs[i] = NULL; // arguments must be followed by NULL to execute 'execvp'-function
    return i;
}

/* Check if command should execute in background */
bool isBackgroundCommand(char *commandArgs[ARGS_BUFFER_SIZE], int argc) {
    return argc > 0 && strcmp(commandArgs[argc - 1], AMPRSND) == 0;
}

/* Execute a command */
void execCommand(char *commandArgs[ARGS_BUFFER_SIZE], int argc) {
    if (argc < 1) // number of arguments is less than 1
        return;
    if (strcmp(commandArgs[0], "exit") == 0) // exit command was entered
        exit(EXIT_SUCCESS);
    

    bool background = isBackgroundCommand(commandArgs, argc); // flag
    pid_t processId = fork();

    if (processId > 0) { // parent process
	    while (!background && wait(NULL) != processId); // wait for completion
    }
    else if (processId == 0) { // child process
        if (execvp(commandArgs[0], commandArgs) < 0) { // execute the command
            printf("An error occured: couldn't find a command \"%s\"\n", commandArgs[0]);
            exit(EXIT_FAILURE);
        }
    }
    else {
	    printf("An error occured: couldn't fork processes\n");
	    exit(EXIT_FAILURE);
    }
}


int main() {
	while (1) {
		printf("> ");
		
		char command[COMMAND_BUFFER_SIZE];
		fgets(command, COMMAND_BUFFER_SIZE, stdin);
        command[strcspn(command, "\n\r")] = 0; // remove trailing newline character
        
        char *commandArgs[ARGS_BUFFER_SIZE];
        int argc = splitCommand(command, commandArgs); // split command into arguments and get number of them
        
        execCommand(commandArgs, argc);
	}

	return EXIT_SUCCESS;
}
