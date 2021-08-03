#include "my_sqrt.h"
#include <stdio.h>
#include <assert.h>
#include <math.h> 
#include <stdlib.h>
#define EPSILON 1e-8

double my_sqrt(double x) {
    double value = 0; 
    double guess = x / 2; 
    while(value != guess) {
        value = guess; 
        guess = ( value + x / value )/ 2; 
    }
    return value; 
}

double my_sqrt_with_log(double x) {
    double value = 0; 
    double guess = x / 2; 
    while(value != guess) {
        printf("%.6f\n", value); 
        value = guess; 
        guess = ( value + x / value )/ 2; 
    }
    return value; 
}

void assertEquals(double x,double y) {
    assert(fabs(x-y) < EPSILON);
}

double my_sqrt_checked(double x) { 
    double root = my_sqrt(x) ; 
    assertEquals(root * root, x); 
    return root ; 
}

void sqrt_program(char* arg) {
    int x = atoi(arg); 
    
    if( x == 0) {
        printf("Illegal Input\n");
    }else{
        if (x < 0) {
            printf("Illegal Number\n"); 
        }else{
            printf("The root of %d is %.6lf\n", x, my_sqrt(x));
        }
    }
}

double my_sqrt_fixed(int x) {
    assert(0 <= x); 
    if(x == 0) {
        return 0 ; 
    }
    return my_sqrt(x) ;
}