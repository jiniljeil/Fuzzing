#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h>
int crashme(char * input, int length) { 

    if ( length > 0 && input[0] == 'b') {
        if (length > 1 && input[1] == 'a') {
            if (length > 2 && input[2] == 'd') { 
                if (length > 3 && input[3] == '!') {
                    return 1; 
                }
            }
        }
    }
    return 0; 
}

int main(void) { 
    char c ; 
    int i = 0 ; 
    char * input = (char *)malloc(sizeof(char) * 1024) ;

    while( (c = getchar()) != EOF) {
        input[i++] = c ; 
    }
    input[i] = 0x0 ; 

    int ret = crashme(input, i); 

    if ( input != NULL ) free(input); 
    return ret; 
}