
#include "../include/mutation.h"
#include <string.h>
#include <time.h> 
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h> 
#include <unistd.h>
#include <dirent.h>
#define BUFF_SIZE 1024 

int store_seed_files(char * seed_dir, char * storage[]) {
    DIR * dp = opendir(seed_dir); 
    struct dirent * ep ; 
    int idx = 0 ; 

    if ( dp != NULL ) {
        while( (ep = readdir(dp)) != NULL ) {
            if( (strlen(ep->d_name) == 1 && ep->d_name[0] == '.') || (strlen(ep->d_name) == 2 && ep->d_name[1] == '.')) continue;
            if( ep->d_type == DT_REG ) {
                storage[idx] = (char *)malloc(sizeof(char) * (strlen(seed_dir) + 1 + strlen(ep->d_name) + 1)); 
                sprintf(storage[idx], "%s/%s", seed_dir, ep->d_name); 
                idx++;
            }
        }
    }else{
        return -1; 
    }
    // the number of seed file 
    return idx; 
}

int delete_random_character(char * deleted_string, char * seed_input, int seed_length) {
    if (seed_input == NULL) return -1 ;
    if (deleted_string == NULL) {
        fprintf(stderr, "[delete_random_character]: Should allocate the space of first parameter.\n"); 
        return -1; 
    }
    if (seed_length == 0) return 0 ;
    int length = seed_length; 

    memset(deleted_string, 0 , seed_length) ;

    int pos = rand() % length;  
    int idx = 0 ; 

    memcpy(deleted_string, seed_input, pos); 

    if (pos != length - 1) {
        memcpy(deleted_string + pos, seed_input + pos + 1, length - pos); 
    }
    deleted_string[length-1] = 0x0; 
    
    return length - 1; 
}

int insert_random_character(char * inserted_string, char * seed_input, int seed_length ) {
    if (seed_input == NULL) return -1; 
    int length = seed_length; 

    memset(inserted_string, 0, seed_length); 

    int pos = rand() % (length + 1); 

    char random_character = (char) (rand() % 96 + 32); // 32 ~ 127 

    memcpy(inserted_string, seed_input, pos); 
    inserted_string[pos] = random_character ; 
    memcpy(inserted_string + pos + 1, seed_input + pos, length - pos);
    inserted_string[length + 1] = 0x0;
    return length + 1 ; 
}

int flip_random_character(char * flip_string, char * seed_input, int seed_length) {
    if (seed_input == NULL) return -1; 
    int length = seed_length ;
    if (length == 0) return 0; 

    memset(flip_string, 0, seed_length) ;

    int pos = rand() % length ; 
    char c = seed_input[pos];  

    int bit = 1 << (rand() % 7); 
    char new_c = (char) ((int)c ^ bit); 

    memcpy(flip_string, seed_input, pos); 
    flip_string[pos] = new_c; 
    memcpy(flip_string + pos + 1, seed_input + pos + 1, length - pos); 
    flip_string[length] = 0x0; 

    return length; 
}

int mutate(char * string, char * seed_input, int seed_length) {
    int (*mutator[3]) (char *, char *, int) = {delete_random_character, insert_random_character, flip_random_character}; 

    int choice = rand() % 3 ;

    return mutator[choice](string, seed_input, seed_length); 
}

int mutate_input(char * input, char * seed_file_storage[] , int order, int mutation) {
    
    int fd = -1; 
    if (access(seed_file_storage[order], R_OK) != -1 ) {
        fd = open(seed_file_storage[order], O_RDONLY);
    }else{
        fprintf(stderr, "file does not exist!\n"); 
        return -1; 
    }
    
    char buf[BUFF_SIZE]; 

    ssize_t s = 0 ; 
    size_t length = 0 ; 
    while ((s = read(fd, buf + s, BUFF_SIZE - 1)) > 0) {
        length += s ;
        buf[length] = 0x0 ; 
    }

    if (fd != -1) close(fd); 
    
    int input_length = 0 ; 
    for(int i = 0 ; i < mutation ;i++) {
        if ((input_length = mutate(input, buf, length)) <= 0) {
            fprintf(stderr, "Mutations error!\n"); 
        } else {
            memcpy(buf, input, input_length); 
            buf[input_length] = 0x0; 
        }
    }

    return input_length ;
}