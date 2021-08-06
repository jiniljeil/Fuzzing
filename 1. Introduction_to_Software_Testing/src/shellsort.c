#include "../include/shellsort.h"

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