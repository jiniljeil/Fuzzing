#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> 

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

int main(void) {
    int x = 0; 
    scanf("%d", &x) ;

    printf("%.6lf\n", my_sqrt(x)); 

    int result = my_sqrt(x) ;
    float expected_result = 2.0 ; 
    if(result == expected_result) {
        printf("Test passed\n");
    }else{
        printf("Test failed"); 
    }

    printf("ASSERT TEST\n"); 
    assert(my_sqrt(4) == 2) ;
    
    assert(fabs(my_sqrt(4) - 2) < EPSILON); 

    // Test pass
    assertEquals(my_sqrt(4), 2); 
    assertEquals(my_sqrt(9), 3); 
    assertEquals(my_sqrt(100), 10); 

    // Generating Test 
    assertEquals(my_sqrt(2) * my_sqrt(2), 2); 
    assertEquals(my_sqrt(3) * my_sqrt(3), 3);
    assertEquals(my_sqrt(42.11) * my_sqrt(42.11), 42.11);

    for(int i = 1; i < 1000; i++) { 
        assertEquals(my_sqrt(i) * my_sqrt(i), i);
    }

    // Timer 
    clock_t start, end ; 
    start = clock(); 
    for(int i = 0 ; i < 10000; i++) {
        assertEquals(my_sqrt(i) * my_sqrt(i), i) ; 
    }
    end = clock(); 
    printf("WORKING TIME: %.6lf\n", (double)(end - start)/CLOCKS_PER_SEC);
    
    // Random
    srand(time(NULL));

    start = clock(); 
    for(int i = 0 ; i < 10000; i++) {
        int x = 1 + rand() * 1000000; 
        assertEquals(my_sqrt(i) * my_sqrt(i), i) ; 
    }
    end = clock(); 
    printf("WORKING TIME: %.6lf\n", (double)(end - start)/CLOCKS_PER_SEC);
    
    printf("%.6lf\n", my_sqrt_checked(2.0)); 

    sqrt_program("4"); 
    sqrt_program("-1");
    sqrt_program("xyzzy");
    
    return 0; 
}