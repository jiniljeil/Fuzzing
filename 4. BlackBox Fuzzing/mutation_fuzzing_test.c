#include "include/mutation.h" 
#include "include/url_parser.h"
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include <time.h> 

void delete_random_character_test() {
    printf("[DELETE RANDOM CHARACTER]\n"); 
    char seed_input[] = "A quick brown fox"; 
    int length = strlen(seed_input); 

    for(int i = 0 ; i < 10; i++) {
        char *str = (char*)malloc(sizeof(char) * length) ; 
        delete_random_character(str, seed_input, length); 
        printf("%s\n", str);  
        free(str); 
    }
}

void insert_random_character_test() { 
    printf("[INSERT RANDOM CHARACTER]\n"); 
    char seed_input[] = "A quick brown fox"; 
    int length = strlen(seed_input) ; 

    for(int i = 0 ; i < 10 ;i++) {
        char * str = (char*)malloc(sizeof(char) * (length + 1 + 1)); 
        insert_random_character(str, seed_input, length) ; 
        printf("%s\n", str); 
        free(str); 
    }  
}

void flip_random_character_test() {
    printf("[FLIP RANDOM CHARACTER]\n"); 
    char seed_input[] = "A quick brown fox";
    int length = strlen(seed_input); 

    for(int i = 0 ; i < 10; i++) {
        char * str = (char*)malloc(sizeof(char) * (length + 1)) ;
        flip_random_character(str, seed_input, length); 
        printf("%s\n", str); 
        free(str); 
    }
}

void mutate_test() {
    printf("[MUTATE TEST]\n"); 
    char seed_input[] = "A quick brown fox";
    int length = strlen(seed_input) * 2;  
    char * str = (char *)malloc(sizeof(char) * length); 
    
    mutate(str, seed_input, length); 
    printf("%s\n", str); 
    free(str); 
}

void multiple_mutations_test() {
    printf("[MULTIPLE MUTATIONS]\n"); 
    char seed_input[] = "http://www.google.com/search?q=fuzzing"; 
    char input[] = "http://www.google.com/search?q=fuzzing"; 
    int length = 0 ; 
    int mutations = 50 ; 

    for (int i = 0 ; i < mutations; i++) {
        length = strlen(input); 
        if ( i % 5 == 0 ) { 
            printf("%d mutations: %s | ", i, input); 
            if (http_program(input) != -1){ 
                printf("Matching!\n"); 
            }else{
                printf("Not matching!\n");
            }
        }
        mutate(input, seed_input, length);
    }
}
int main(void) {
    
    srand(time(NULL)); 
    
    delete_random_character_test(); 

    insert_random_character_test(); 

    flip_random_character_test(); 

    mutate_test(); 

    multiple_mutations_test(); 
}