#include <stdio.h>
#include <stdlib.h>

int main() {
	printf("Input N, size of array:\n");
	int n; scanf("%d", &n);
	
	if (n < 0)
		printf("N must be non-negative\n");
	
	// allocate memory for array
	int* arr = (int*)(malloc(sizeof(int) * n));
	
	// fill the array
	for (int i = 0; i < n; ++i)
		arr[i] = i;
	
	// print the array
	printf("The array: ");
	for (int i = 0; i < n; ++i)
		printf("%d ", arr[i]);
	printf("\n");
	
	// deallocate memory for array
	free(arr);
	
	return 0;
}
