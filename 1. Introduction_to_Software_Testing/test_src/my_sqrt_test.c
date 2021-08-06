#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> 
#include "../include/my_sqrt.h"

int main(void) {
    int x = 0; 
    printf("Enter a number: ");
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