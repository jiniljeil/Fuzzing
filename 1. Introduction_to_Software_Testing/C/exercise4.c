#include <stdio.h>
#include <math.h> 
#include <assert.h>
#include "include/my_sqrt.h"

int main(void) {
    printf("[Exercise 4: To Infinity and Beyond]\n"); 
    printf("Infinity sqrt: %.6f\n", my_sqrt_fixed(__FLT_MAX__ * 1000)); 
}