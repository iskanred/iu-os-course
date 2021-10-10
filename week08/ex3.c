#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MB 1024 * 1024
#define MEMORY_BLOCK 100 * MB

int main() {
    
	for (int i = 0; i < 10; ++i) {
		int *p_mem = (int*)(malloc(MEMORY_BLOCK));

        if (p_mem == NULL) {
            printf("Couldn't allocate a memory on %dth iteration\n", i + 1);
        }            

        // initialize allocated memory with zeros
		memset(p_mem, 0, MEMORY_BLOCK);
		sleep(1);
	}


	return EXIT_SUCCESS;
}

/* OUTPUT: ================================================================================
PID     USER      PR  NI    VIRT    RES    SHR S  %CPU  %MEM   TIME+   COMMAND
11984   iskanred  20   0  309700 308236   1192 S   3,0   5,1   0:00.09 ex3                                                 
2380    iskanred  20   0   16,5g  72284  44364 S   2,0   1,2   4:35.33 chrome                                              
2425    iskanred  20   0   16,3g  43636  34104 S   2,0   0,7   1:14.58 chrome                                              
11331   iskanred  20   0   20,4g  34816  24936 S   2,0   0,6   0:17.95 chrome                                              
11954   root      20   0       0      0      0 I   1,0   0,0   0:00.02 kworker/u32:0-phy0                                  
11985   iskanred  20   0   11988   4000   3224 R   1,0   0,1   0:00.03 top                                                 
1       root      20   0  168156   4900   3372 S   0,0   0,1   0:01.82 systemd
===========================================================================================

We see that our process consumed 5.1% of available memory and became the most memory-comsuming process unitl it finishes
*/
