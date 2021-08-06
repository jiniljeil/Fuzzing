#include <stdlib.h>
#include <string.h>
#include <stdio.h> 
// #define TEST
/* 
clang -fsanitize=address -g -o program program.c
*/

int main(int argc, char** argv) {
    /* Create an array with 100 bytes, initialized with 42 */
    char *buf = malloc(100);
    memset(buf, 42, 100);

    /* Read the N-th element, with N being the first command-line argument */
    int index = atoi(argv[1]);
    
#ifdef TEST
    char *buff = malloc(100); 
    memset(buff, 42, 100);
#endif 
    char val = buf[index];

    /* Clean up memory so we don't leak */
    free(buf);
    return val;
}