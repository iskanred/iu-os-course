#include <stdio.h>
#include <stdlib.h>


int main () {
	// we need to initalize s first before dereference it
	char **s = (char**)(malloc(sizeof(char*)));
	char foo[] = "Hello World";
	
	// after initialization we can dereference it
	*s = foo;
	printf("s is %s\n", *s);
	
	// equivalent to previous assignment
	s[0] = foo;
	printf ("s[0] is %s\n", s[0]);
	
	// deallocate memory before end of the program
	free(s);
	
	return 0;
}
