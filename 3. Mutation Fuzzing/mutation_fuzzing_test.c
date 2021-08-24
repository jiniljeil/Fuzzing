#include "include/mutation.h" 
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include <time.h> 

void delete_random_character_test() {
    printf("[DELETE RANDOM CHARACTER]\n"); 
    char seed_input[] = "A quick brown fox"; 

    for(int i = 0 ; i < 10; i++) {
        char *str = delete_random_character(seed_input); 
        printf("%s\n", str);  
        free(str); 
    }
}

void insert_random_character_test() { 
    printf("[INSERT RANDOM CHARACTER]\n"); 
    char seed_input[] = "A quick brown fox"; 
     
    for(int i = 0 ; i < 10 ;i++) {
        char * str = insert_random_character(seed_input) ; 
        printf("%s\n", str); 
        free(str); 
    }  
}

void flip_random_character_test() {
    printf("[FLIP RANDOM CHARACTER]\n"); 
    char seed_input[] = "A quick brown fox";

    for(int i = 0 ; i < 10; i++) {
        char * str = flip_random_character(seed_input); 
        printf("%s\n", str); 
        free(str); 
    }
}

void mutate_test() {
    printf("[MUTATE TEST]\n"); 
    char seed_input[] = "A quick brown fox";

    char * str = mutate(seed_input); 
    printf("%s\n", str); 
    free(str); 
}
int main(void) {
    
    srand(time(NULL)); 
    
    delete_random_character_test(); 

    insert_random_character_test(); 

    flip_random_character_test(); 

    mutate_test(); 
}