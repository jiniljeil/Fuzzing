#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "include/shellsort.h"

void part0_basic() {
    int random_size = 1 + rand() % 10000; 
    printf("RANDOM SIZE: %d\n", random_size);
    int* random_list = randomList(random_size); 

    printf("\n[RANDOM SHELLSORT]\n");
    int* random_sort = shellsort(random_list, random_size); 
    printf("Random List Sorted: %s\n", (is_sorted(random_sort, random_size) == 1) ? "True" : "False"); 

    int a[4] = {5, 6, 99, 7}; 
    printf("\nFirst element: %d, length: %lu\n", a[0], sizeof(a)/sizeof(int)); 

    int a_test[3] = {3, 2, 1}; 
    int b_test[3] = {1, 3, 2}; 
    printf("\nPermutation: [3, 2, 1], [1, 3, 2]: %s\n", (is_permutation(a_test, b_test, 3, 3) == 1) ? "True" : "False");

    int a_test_2[4] = {3, 2, 5, 6}; 
    int b_test_2[4] = {1, 3, 6, 4}; 
    printf("\nPermutation: [3, 2, 5, 6], [1, 3, 6, 4]: %s\n", (is_permutation(a_test_2, b_test_2, 3, 3) == 1) ? "True" : "False");
}

void part1_manual_test_cases() {
    int test_1[10] = {18, 292, 191, 2381, 2251, 28123, 92913, 8, 83, 110}; 
    int * test_1_sort = shellsort(test_1, 10); 
    printf("\nPermutation: %s\n", (is_permutation(test_1,test_1_sort, 10, 10) == 1) ? "True" : "False");

    int test_2[8] = {1, 85, 281, 293, 8, 7, -1, -283}; 
    int * test_2_sort = shellsort(test_2, 8); 
    printf("\nPermutation: %s\n", (is_permutation(test_2,test_2_sort, 8, 8) == 1) ? "True" : "False");

    int test_3[5] = {5, 1, 10, -293, -1283}; 
    int * test_3_sort = shellsort(test_3, 5); 
    printf("\nPermutation: %s\n", (is_permutation(test_3,test_3_sort, 5, 5) == 1) ? "True" : "False");

    int test_4[6] = {-1923, -12939124, -18238128, 0, 12398821, 382841}; 
    int * test_4_sort = shellsort(test_4, 6); 
    printf("\nPermutation: %s\n", (is_permutation(test_4, test_4_sort, 6, 6) == 1) ? "True" : "False");
}

void part2_random_inputs() {
    int * random_per = randomList(1000);
    int * per_sort = shellsort(random_per, 1000); 
    printf("Random Permutatoin: %s\n", (is_permutation(random_per, per_sort, 1000,1000) == 1) ? "True" : "False"); 
}

int main(void) {
    // shellsort 
    part0_basic();
    part1_manual_test_cases(); 
    part2_random_inputs();
    return 0;
}