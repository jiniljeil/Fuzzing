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


int* shellsort(int *elems, int size){
    int elems_size = size; 
    int * sorted_elems = (int*)malloc(sizeof(int) * elems_size); 
    for(int i = 0 ; i < size ; i++) sorted_elems[i] = elems[i];

    int gaps[8] = {701, 301, 132, 57, 23, 10, 4, 1}; 
    for(int i = 0 ; i < 8; i++) {
        int gap = gaps[i]; 
        for(int j = gap; j < elems_size; j++) {
            int tmp = sorted_elems[j]; 
            int k = j ;
            while(k >= gap && sorted_elems[k - gap] > tmp) {
                sorted_elems[k] = sorted_elems[k - gap]; 
                k -= gap; 
            }
            sorted_elems[k] = tmp; 
        }
    }
    return sorted_elems; 
}
 
int is_sorted(int *elems, int size) {
    for(int i = 0 ; i < size - 1; i++) if(elems[i] > elems[i+1]) return 0;
    return 1; 
}

int is_permutation(int *a, int *b, int a_size, int b_size) {
    if(a_size == b_size) {
        int *b_check = (int*)malloc(sizeof(int) * b_size); 
        memset(b_check, 0, sizeof(int) * b_size); 
        for(int i = 0 ; i < a_size; i++){
            for(int j = 0 ; j < b_size; j++) {
                if(a[i] == b[j] && b_check[j] == 0) {
                    b_check[j] = 1; 
                    break; 
                }
            }
        }
        int ret = 1 ; 
        for(int i = 0 ; i < b_size; i++) {
            if(b_check[i] == 0) {
                ret = 0;
                break; 
            }
        }
        free(b_check); 
        return ret; 
    }else{
        return 0; 
    }
}

double *quadratic_solver(int a, int b, int c) {
    int q = b * b - 4 * a * c ; // b^2 - 4ac
    double * sol = (double*)malloc(sizeof(double) * 2) ; 
    sol[0] = (-b + my_sqrt_fixed(q)) / (2*a); 
    sol[1] = (-b - my_sqrt_fixed(q)) / (2*a); 
    return sol; 
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
    
   
    int arr[3] = {3, 2, 1}; 
    int arrsize = 3;  
    int* _shellsort = shellsort(arr, arrsize); 
    
    for(int i = 0 ; i < arrsize; i++) {
        printf("%d ", _shellsort[i]);
    }
    printf("\n");

    int a[4] = {5, 6, 99, 7}; 
    printf("First element: %d, length: %lu\n", a[0], sizeof(a)/sizeof(int)); 

    int b[3] = {3, 5, 9}; 
    printf("Sorted: [3, 5, 9]: %s\n", (is_sorted(b, 3) == 1) ? "True" : "False"); 

    int a_test[3] = {3, 2, 1}; 
    int b_test[3] = {1, 3, 2}; 
    printf("Permutation: [3, 2, 1], [1, 3, 2]: %s\n", (is_permutation(a_test,b_test, 3, 3) == 1) ? "True" : "False");

    double *q_solver = quadratic_solver(3, 4, 1); 
    printf("(%.6lf, %.6lf)", q_solver[0], q_solver[1]); 

    free(_shellsort);
    free(q_solver) ;
    return 0; 
}