#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1001

int main() {
	char command[BUFFER_SIZE];	
	
	while(1) {
		printf("> ");
		scanf("%s", command);
		system(command);
	}
	
	return EXIT_SUCCESS;
}
