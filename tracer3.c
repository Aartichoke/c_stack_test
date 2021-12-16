#include <stdio.h>
#include <malloc.h>

int A;
int B;

int function(int depth) {
    printf("function = %p\n",&function);
    int rc;
    char buf[5];
    char *stuff = (char *) malloc(16*sizeof(char));

        printf("stuff = %p\n",&stuff);
        printf("rc = %p\n",&rc);
        printf("buf = %p\n",&buf);

    if(depth < 10) {
        rc = function(depth+1);
    }
    else
	rc = 0;
    free(stuff);

    return rc;
}

int main(int argc, char* argv[]) {
    printf("printf = %p\n",&printf);
    printf("main = %p\n",&main);
    int x;
    char *buffer = (char *) malloc(128*sizeof(char));
    int  *array = (int *) malloc(128*sizeof(int));
    x = function(1);
    printf("buffer = %p\n",&buffer);
    printf("array = %p\n",&array);
    printf("x = %p\n",&x);
    return 0;
}
