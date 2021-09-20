#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* printThread(void *threadIndex) {
    printf("\t>> Hello from thread #%d\n", *((int*)threadIndex));

    pthread_exit(NULL);
    return NULL;
}


int main() {
    printf("Input number of threads to be created\n");
    int n; scanf("%d", &n);

    pthread_t *threads = (pthread_t*)(malloc(n * sizeof(pthread_t))); // allocate memory for n threads
    
    for (int i = 0; i < n; ++i) {
        int errorStatus = pthread_create(&threads[i], NULL, printThread, &i);

        if (errorStatus) {
            printf("ERROR IN CREATING A THREAD!\n");
        }
        else {
            printf("Thread was created\n");
        }

        pthread_join(threads[i], NULL);
    }

    pthread_exit(NULL);
    return EXIT_SUCCESS;
}
