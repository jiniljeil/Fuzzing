#include <stdio.h>
#include <math.h> 

double my_sqrt(double x) {
    double value = 0; 
    double guess = x / 2; 
    while(value != guess) {
        value = guess; 
        guess = ( value + x / value )/ 2; 
    }
    return value; 
}

double my_sqrt_fixed(int x) {
    assert(0 <= x); 
    if(x == 0) {
        return 0 ; 
    }
    return my_sqrt(x) ;
}

int main(void) {
    printf("[Exercise 4: To Infinity and Beyond]\n"); 
    unsigned long long infinity =  __FLT_MAX__ * 1000; 
    printf("Infinity sqrt: %.6f\n", my_sqrt_fixed(infinity)); 
}