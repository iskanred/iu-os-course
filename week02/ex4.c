#include <stdio.h>

void  swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}


int main() {
	printf("Please input two integers\n");
	int a, b;

	if (scanf("%d %d", &a, &b) != 2) {
		printf("Input mismatch: excpected two integers\n");
		return 0;
	}

	swap(&a, &b);

	printf("%d %d\n", a, b);

	return 0;
}
