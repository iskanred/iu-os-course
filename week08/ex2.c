#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MB 1024 * 1024
#define MEMORY_BLOCK 500 * MB

int main() {
    
	for (int i = 0; i < 10; ++i) {
		int *p_mem = (int*)(malloc(MEMORY_BLOCK));

        if (p_mem == NULL) {
            printf("Couldn't allocate a memory on %dth iteration\n", i + 1);
        }            

        // initialize allocated memory with zeros
		memset(p_mem, 0, MEMORY_BLOCK);

        printf("500 MB of memory were allocated\n");
		sleep(1);
	}


	return EXIT_SUCCESS;
}

/*
procs -----------memory---------- ---swap-- -----io---- -system-- ------cpu-----
 r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st
 0  1 1185536 4624044   7652 324120   12  201   175   273 1538 2107 17  7 76  0  0
500 MB of memory were allocated
 0  0 1185536 4111572   7652 324372   44    0    44     0 2231 1650  2  5 93  0  0
500 MB of memory were allocated
 0  0 1185536 3598248   7652 324372    0    0     0     0 1841 1403  2  4 93  0  0
500 MB of memory were allocated
 0  0 1185024 3084892   7944 324860  432    0  1116   128  904 1340  3  3 94  1  0
500 MB of memory were allocated
 2  0 1184768 2569016   8428 327556   88    0  2093     4 1081 1698  3  5 92  0  0
500 MB of memory were allocated
 0  0 1183232 2044140  10264 336900 1140    0  5616     0 1601 2947  1 13 85  1  0
500 MB of memory were allocated
 1  0 1183232 1530816  10264 336900    0    0     0     0  675  964  2  4 94  0  0
 1  0 1183232 1302188  10264 336900    0    0     0     4  630  883  2  2 96  0  0
500 MB of memory were allocated
 0  0 1183232 1019664  10264 336900    0    0     0     0  706 1034  2  2 96  0  0
500 MB of memory were allocated
 0  0 1183232 506340  10272 336892    0    0    36    52  760 1043  2  4 94  0  0
500 MB of memory were allocated
 0  0 1202176 136792   3336 234788   36 31492  9060 31700 1448 1827  2 11 86  1  0
 2  1 1558728  94976    528 142688   16 359836 39732 359952 26864 4830  3 30 63  4  0
500 MB of memory were allocated
 0  0 1702388 125880    536 167776 1804 148584 46152 148620 21966 3472  1 13 82  4  0
 1  0 1511924 5087444   1072 188820  164    0 22160     0 1034 1521  1  5 93  1  0
 0  0 1509876 5053928   1504 217832 2384    0 30860   604 1515 2299  1  1 95  2  0
 0  0 1509620 5053612   1504 218296  108    0   768     0  691  962  1  0 98  0  0
 0  0 1508084 5045216   1512 224956 2252    0  8720    40 1051 1670  1  1 97  1  0
 0  0 1508084 5045280   1512 225008   44    0   120     0  545  806  1  1 98  0  0
 0  0 1508084 5044776   1520 225512   20    0   508    48  634  912  1  1 97  1  0
==============================================================================================
We see that amount of free memory is decreasing since new memory allocated for the process, also
    we see that after allocation big amount of memory 'si' and 'so' became non-zero,
    it means the system has no enogh memory to hold the process memory and it loads memory blocks to
    the disk drive
*/
