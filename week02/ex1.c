#include <limits.h>
#include <float.h>
#include <stdio.h>

int main() {
    int intVar = INT_MAX;
    float floatVar = FLT_MAX;
    double doubleVar = DBL_MAX;

    printf("int var has a size = %lu bytes\n", sizeof(intVar));
    printf("float var has a size = %lu bytes\n", sizeof(floatVar));
    printf("double var has a size = %lu bytes\n", sizeof(doubleVar));

    printf("\n");

    printf("int var has a value = %d\n", intVar);
    printf("float var has a value = %f\n", floatVar);
    printf("double var has a value = %f\n", doubleVar);

    return 0;
}
