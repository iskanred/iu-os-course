#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>


int main() {
    int n = 3;

	for (int i = 0; i < n; ++i) {
		fork();
		sleep(5);
	}
	
	return EXIT_SUCCESS;
}

/*
    After running this program in a background and run 'pstree':
    ──bash─┬─ex2─┬─ex2─┬─ex2───ex2
           │     │     └─ex2
           ├─ex2───ex2
           │     └─ex2
           └─pstree
    
    We see that each process creates (n - i) children where 'i' is a current index of for-loop
    Thus, it will always create (2^n) in total
*/
