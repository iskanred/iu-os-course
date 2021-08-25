#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool isNaturalNumber(char* str) {
    unsigned int STRLEN = strlen(str);
    for (int idx = 0; idx < STRLEN; ++idx)
        if (!isDigit(str[idx]))
            return false;

    return true;
}


int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("Too few arguments\n");
        return 0;
    }

    if (argc > 2) {
        printf("Too many arguments\n");
        return 0;
    }

    if (!isNaturalNumber(argv[1])) {
        printf("Input mismatch: n must be a natural number\n");
        return 0; 
    }
    

	int n; sscanf(argv[1], "%d", &n);


	for (int h = 1; h <= n; ++h) {
		// Print spaces
		for (int s = (2 * n -  2 * h) / 2; s >= 0; --s)
			printf(" ");

		// Print asterisks
		for (int w = 1; w <= 2 * h - 1; ++w) {
			printf("*");
		}

		printf("\n");
	}

	return 0;
}
