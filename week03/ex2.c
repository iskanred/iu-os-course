#include <stdio.h>
#include <stdlib.h>


void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}


void bubble_sort(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (arr[i] > arr[j])
                swap(&arr[i], &arr[j]);
        }    
    }
}

void input_int_array(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        if (scanf("%d", &arr[i]) != 1) {
        	printf("Input mismatch: expected an integer\n");
        	exit(0);
        }
	}
}

void print_int_array(int arr[], int size) {
    for (int i = 0; i < size; ++i)
        printf("%d ", arr[i]);

    printf("\n");
}



int main() {
    printf("Input a size of array:\n");
	
	int n;
	
	// check input
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Input mismatch: expected a positive integer\n");
        return 0;
    }


    int* arr = malloc(n * sizeof(int));
    
    // input array
    printf("Input %d integers:\n", n);
    input_int_array(arr, n);

    // sort array
    bubble_sort(arr, n);
    
    // print array
    printf("Sorted array:\n");
    print_int_array(arr, n);
       
    // free memory allocated in heap
    free(arr);
   
    return 0;
}
