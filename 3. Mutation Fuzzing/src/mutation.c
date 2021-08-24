
#include "../include/mutation.h"
#include <string.h>
#include <time.h> 
#include <stdlib.h>
#include <stdio.h>

char * delete_random_character(char * seed_input) {
    if (seed_input == NULL) return NULL ;
    int length = strlen(seed_input); 
    char * deleted_string = (char*)malloc(sizeof(char) * (length + 1)); 

    int pos = rand() % length;  
    int idx = 0 ; 

    memcpy(deleted_string, seed_input, pos); 

    if (pos != length) {
        memcpy(deleted_string + pos, seed_input + pos + 1, length - pos); 
    }
    deleted_string[length] = 0x0; 
    
    return deleted_string ; 
}

char * insert_random_character(char * seed_input) {
    if (seed_input == NULL) return NULL; 
    int length = strlen(seed_input); 
    char * inserted_string = (char*)malloc(sizeof(char) * (length + 1 + 1));

    int pos = rand() % (length + 1); 

    char random_character = (char) (rand() % 96 + 32); // 32 ~ 127 

    memcpy(inserted_string, seed_input, pos); 
    inserted_string[pos] = random_character ; 
    memcpy(inserted_string + pos + 1, seed_input + pos, length - pos);
    inserted_string[length + 1] = 0x0;
    return inserted_string ; 
}

char * flip_random_character(char * seed_input) {
    if (seed_input == NULL) return NULL; 

    int length = strlen(seed_input); 
    if (length == 0) return seed_input; 

    int pos = rand() % length ; 
    char c = seed_input[pos];  

    int bit = 1 << (rand() % 7); 
    char new_c = (char) ((int)c ^ bit); 

    char * flip_string = (char*)malloc(sizeof(char) * (length + 1)); 
    memcpy(flip_string, seed_input, pos); 
    flip_string[pos] = new_c; 
    memcpy(flip_string + pos + 1, seed_input + pos + 1, length - pos); 
    flip_string[length] = 0x0; 

    return flip_string ;
}

char * mutate(char * seed_input) {
    char * (*mutator) (char *) ; 

    int choice = rand() % 3 ; 

    switch(choice) {
        case 0: 
            mutator = &delete_random_character ; 
            break ;
        case 1: 
            mutator = &insert_random_character ; 
            break ; 
        case 2: 
            mutator = &flip_random_character ; 
            break ;
    }

    return mutator(seed_input); 
}