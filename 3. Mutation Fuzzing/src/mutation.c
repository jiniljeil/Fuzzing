
#include "../include/mutation.h"
#include <string.h>
#include <time.h> 
#include <stdlib.h>
#include <stdio.h>

int delete_random_character(char * deleted_string, char * seed_input, int seed_length) {
    if (seed_input == NULL) return -1 ;
    if (deleted_string == NULL) {
        fprintf(stderr, "[delete_random_character]: Should allocate the space of first parameter.\n"); 
        return -1; 
    }
    int length = seed_length; 

    int pos = rand() % length;  
    int idx = 0 ; 

    memcpy(deleted_string, seed_input, pos); 

    if (pos != length - 1) {
        memcpy(deleted_string + pos, seed_input + pos + 1, length - pos); 
    }
    deleted_string[length-1] = 0x0; 
    
    return 1; 
}

int insert_random_character(char * inserted_string, char * seed_input, int seed_length ) {
    if (seed_input == NULL) return -1; 
    int length = seed_length; 

    int pos = rand() % (length + 1); 

    char random_character = (char) (rand() % 96 + 32); // 32 ~ 127 

    memcpy(inserted_string, seed_input, pos); 
    inserted_string[pos] = random_character ; 
    memcpy(inserted_string + pos + 1, seed_input + pos, length - pos);
    inserted_string[length + 1] = 0x0;
    return 1 ; 
}

int flip_random_character(char * flip_string, char * seed_input, int seed_length) {
    if (seed_input == NULL) return -1; 
    int length = seed_length ;
    if (length == 0) return 0; 

    int pos = rand() % length ; 
    char c = seed_input[pos];  

    int bit = 1 << (rand() % 7); 
    char new_c = (char) ((int)c ^ bit); 

    memcpy(flip_string, seed_input, pos); 
    flip_string[pos] = new_c; 
    memcpy(flip_string + pos + 1, seed_input + pos + 1, length - pos); 
    flip_string[length] = 0x0; 

    return 1; 
}

int mutate(char * string, char * seed_input, int seed_length) {
    int (*mutator[3]) (char *, char *, int) = {delete_random_character, insert_random_character, flip_random_character}; 

    int choice = rand() % 3 ;

    return mutator[choice](string, seed_input, seed_length); 
}