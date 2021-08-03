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

int* randomList(int size) {
    int* list = (int*)malloc(sizeof(int) * size); 

    for(int i = 0 ; i < size ;i++) {
        list[i] = rand(); 
    }
    
    return list; 
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

double* quadratic_solver(int a, int b, int c) {
    // ax^2 + bx + c = 0 
    double * sol ; 
    if (a == 0) {
        if (b == 0) {
            if (c == 0) {
                sol = (double*)malloc(sizeof(double)) ; 
                sol[0] = 0 ; 
                return sol; 
            }else{
                return NULL; 
            }   
        }else{
            sol = (double*)malloc(sizeof(double)) ; 
            sol[0] = - c / b ; 
            return sol; 
        }
    }

    int q = b * b - 4 * a * c ; // b^2 - 4ac

    if( q < 0 ) return NULL; 
    if( q == 0 ) {
        sol = (double*)malloc(sizeof(double)) ; 
        sol[0] = -b / 2 * a; 
        return sol; 
    }
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
    
    // shellsort 
    printf("\n[SHELLSORT]\n"); 
    int arr[3] = {3, 2, 1}; 
    int arrsize = 3;  
    int* _shellsort = shellsort(arr, arrsize); 

    for(int i = 0 ; i < arrsize; i++) {
        printf("%d ", _shellsort[i]);
    }
    printf("\n");

    // SORT ASSERT
    
    int sorted[3] = {1, 2, 3}; 
    for(int i = 0 ; i < arrsize; i++) {
        assert(_shellsort[i] == sorted[i]);
    }
    int random_size = 1 + rand() % 10000; 
    printf("RANDOM SIZE: %d\n", random_size);
    int* random_list = (int*)malloc(sizeof(int) * random_size);

    for(int i = 0 ; i < random_size; i++) {
        random_list[i] = rand(); 
    }

    printf("\n[RANDOM SHELLSORT]\n");
    int* random_sort = shellsort(random_list, random_size); 
    // for(int i = 0 ; i < random_size; i++) {
    //     printf("%d ", random_sort[i]);
    // }
    // printf("\n");
     // int b[3] = {3, 5, 9}; 
    printf("Random List Sorted: %s\n", (is_sorted(random_sort, random_size) == 1) ? "True" : "False"); 

    int a[4] = {5, 6, 99, 7}; 
    printf("\nFirst element: %d, length: %lu\n", a[0], sizeof(a)/sizeof(int)); 

    int a_test[3] = {3, 2, 1}; 
    int b_test[3] = {1, 3, 2}; 
    printf("\nPermutation: [3, 2, 1], [1, 3, 2]: %s\n", (is_permutation(a_test,b_test, 3, 3) == 1) ? "True" : "False");

    int * random_per = randomList(1000);
    int * per_sort = shellsort(random_per, 1000); 
    printf("Random Permutatoin: %s\n", (is_permutation(random_per, per_sort, 1000,1000) == 1) ? "True" : "False"); 
    // Error 
    // a = 0 (a division by zero)
    // q < 0 (q is a negative value)
    double *q_solver ; 
    // q_solver = quadratic_solver(3, 4, 1); // (a, b, c)  
    // q_solver = quadratic_solver(0, 0, 1); 

    printf("\nPart 3: Odds and Ends\n[Quadriatic Solver] [1, 2, 3]\n");
    q_solver = quadratic_solver(1, 2, 3); 
    if (q_solver == NULL) printf("해가 존재하지 않습니다.\n");
    else printf("(%.6lf, %.6lf)\n", q_solver[0], q_solver[1]); 


    unsigned long long combination = 1; 
    combination = (combination << 63); 
    
    unsigned long long year = (60 * 60 * 24 * 365) ;
    unsigned long long second = 1e9; 

    printf("\nIf we can do a billion tests per second, how many years would we have to wait?\n"); 
    printf("Year: %llu\n", (combination / (second * year)) * 2 );

    printf("[Exercise 4: To Infinity and Beyond]\n"); 
    unsigned long long infinity =  __FLT_MAX__ * 1000; 
    printf("Infinity sqrt: %.6f\n", my_sqrt_fixed(infinity)); 

    free(_shellsort);
    free(q_solver) ;
    return 0; 
}