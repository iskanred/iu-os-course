#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE 1001

int main() {
    	printf("Please be aware that maximum size of the input string is 1000 characters\n");
	char str[BUFFER_SIZE], reverse[BUFFER_SIZE];
	fgets(str, BUFFER_SIZE, stdin);


	unsigned int STRLEN = strlen(str);

	for (int idx = 0; idx < STRLEN; ++idx) {
		reverse[idx] = str[STRLEN - 1 - idx];
	}


	printf("The output:");
	puts(reverse);

	return 0;
}
