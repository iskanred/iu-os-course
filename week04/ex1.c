#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>


int main() {
	pid_t processId = fork();
	int n = 10;
	
	for (int i = 0; i <= n; ++i) {
		if (processId > 0) {	// parent process
			printf("Hello from parent [%d - %d]\n", processId, i);
		}
		else if (processId == 0) { // child process
			printf("Hello from child [%d - %d]\n", processId, i);
		}
		else {
			printf("An error occured");
			return EXIT_FAILURE;
		}
	}
	
	return EXIT_SUCCESS;
}

/* 
	The output shows us different ways of execution and processes management
	Child and parent processes execute in different ways (one by another, sequentially, random order)
*/

