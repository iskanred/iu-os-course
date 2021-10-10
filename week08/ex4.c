#include <sys/resource.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MB 1024 * 1024
#define MEMORY_BLOCK 500 * MB


int main() {
    struct rusage usage;    

	for (int i = 0; i < 10; ++i) {
		int *p_mem = (int*)(malloc(MEMORY_BLOCK));

        if (p_mem == NULL) {
            printf("Couldn't allocate a memory on %dth iteration\n", i + 1);
        }            

        // initialize allocated memory with zeros
		memset(p_mem, 0, MEMORY_BLOCK);
        // get current usage
        getrusage(RUSAGE_SELF, &usage);


        printf("\n500 MB of memory were allocated\n");
        printf("\tSystem CPU time used: %ld.%06ld sec\n", usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);
        printf("\tMaximum resident set size: %ld\n", usage.ru_maxrss);
        printf("\tIntegral shared memory size: %ld\n", usage.ru_ixrss);
        printf("\tIntegral unshared data size: %ld\n", usage.ru_idrss);
        printf("\tIntegral unshared stack size: %ld\n", usage.ru_isrss);
   
		sleep(1);
	}


	return EXIT_SUCCESS;
}
