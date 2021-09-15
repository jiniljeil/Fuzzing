
#include "../include/mutation.h"
#include <string.h>
#include <time.h> 
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h> 
#include <unistd.h>
#include <dirent.h>
#define BUFF_SIZE 1024 
#define PATH_MAX 4096


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

int add_seed_file(char * seed_dir, char * seed_input[], int * num_of_seed_files, char * input, int input_len) {
    char path[PATH_MAX]; 
    ssize_t size = 0 ; 

    int path_length = sprintf(path, "%s/seed%d", seed_dir, *num_of_seed_files); 
    path[path_length] = 0x0; 

    seed_input[*num_of_seed_files] = (char *)malloc(sizeof(char) * (path_length + 1)); 

    strcpy(seed_input[*num_of_seed_files], path); 

    int fd ; 

    if ((fd = open(path, O_WRONLY | O_CREAT, 0644)) == -1) {
        perror("Cannot open input file\n"); 
        return -1 ;
    }
    
    int sent = 0 ; 
    while(sent < input_len) {
        sent += write(fd, input, input_len - sent); 
    }

    if ( sent != input_len) {
        perror("Write error!\n"); 
        return -1;
    }

    return (++*num_of_seed_files); 
}

int delete_random_character(char * deleted_string, char * seed_input, int seed_length) {
    if (seed_input == NULL) return -1 ;
    if (deleted_string == NULL) {
        fprintf(stderr, "[delete_random_character]: Should allocate the space of first parameter.\n"); 
        return -1; 
    }
    if (seed_length == 0 || seed_length > BUFF_SIZE) return 0 ;
    int length = seed_length; 

    memset(deleted_string, 0 , seed_length) ;

    int byte_size[3] = {1, 2, 4}; 
    int random_byte = 0 ;
    for(int i = 0 ; i < 3; i++) {
        if (length > byte_size[2 - i]) { 
            random_byte = rand() % (3 - i); 

            int pos = rand() % (length - byte_size[random_byte]);  
            int idx = 0 ; 

            memcpy(deleted_string, seed_input, pos); 
             
            if (pos != length - byte_size[random_byte]) {
                memcpy(deleted_string + pos, seed_input + pos + byte_size[random_byte], length - pos - byte_size[random_byte]); 
            }
            deleted_string[length-byte_size[random_byte]] = 0x0; 
            break;  
        }
    }
    
    return length - byte_size[random_byte]; 
}

int insert_random_character(char * inserted_string, char * seed_input, int seed_length) {
    if (seed_input == NULL) return -1; 
    int length = seed_length; 

    memset(inserted_string, 0, seed_length); 

    int byte_size[3] = {1, 2, 4} ; 
    int random_byte = 0 ; 

    for(int i = 0 ; i < 3 ; i++) {
        if (BUFF_SIZE > byte_size[2 - i] + length) {
            random_byte = rand() % (3 - i) ; 
            break; 
        }
    }

    char copy_input[BUFF_SIZE] ;  
    if (seed_length < BUFF_SIZE) {
        memcpy(copy_input, seed_input, seed_length); 
        copy_input[seed_length] = 0x0;  
    }else{
        return length ; 
    }
    
    for(int i = 0 ; i < byte_size[random_byte] ; i++) {
        int pos = rand() % (length + 1); 
        char random_character = (char) (rand() % 96 + 32); // 32 ~ 127 

        memcpy(inserted_string, copy_input, pos); 
        inserted_string[pos] = random_character; 
        memcpy(inserted_string + pos + 1, copy_input + pos, length - pos);

        length++; 
        memcpy(copy_input, inserted_string, length) ;
        copy_input[length] = 0x0; 
    }
    
    return length ; 
}

int bit_flip_random_character(char * flip_string, char * seed_input, int seed_length) {
    if (seed_input == NULL) return -1; 
    int length = seed_length ;
    if (length == 0) return 0; 

    memset(flip_string, 0, seed_length) ;

    int pos = rand() % length ; 
    char c = seed_input[pos];  

    int bit_size[3] = {1, 2, 4}; 

    for(int i = 0 ; i < 3 ; i++) {
        if (length > bit_size[2 - i]) {
            int random_bit = rand() % (3 - i) ;
            int bit = 1 << (rand() % (7 - bit_size[random_bit])) ;
            char new_c = (char) ((int)c ^ bit); 
            
            memcpy(flip_string, seed_input, seed_length) ; 
            flip_string[pos] = new_c; 
            flip_string[seed_length] = 0x0;
            break ;             
        }
    }

    return length; 
}
int byte_flip_random_character(char * byte_flip_string, char * seed_input, int seed_length) {
    if (seed_input == NULL) return -1; 
    int length = seed_length; 
    if (length == 0) return 0 ;

    memset(byte_flip_string, 0, seed_length); 

    int byte_size[3] = {1, 2, 4}; 

    for(int i = 0 ; i < 3; i++) {
        if (length > byte_size[2 - i]) {
            int byte = rand() % (3 - i) ;
            int pos = rand() % (length - byte_size[byte]);
            
            memcpy(byte_flip_string, seed_input, seed_length); 

            for(int b = 0 ; b < byte_size[byte]; b++) {
                char c = seed_input[pos + b] ;
                char new_c = (char) ( c ^ 0xff ); 

                byte_flip_string[pos + b] = new_c; 
            }
            byte_flip_string[length] = 0x0 ;
            break; 
        }
    }
    return length; 
}

int byte_simple_arithmatic(char * arith_string, char * seed_input, int seed_length) { 
    if (seed_input == NULL) return -1; 
    int length = seed_length ; 
    if (length == 0) return 0; 

    int byte_size[3] = {1, 2, 4}; 

    for(int i = 0 ; i < 3 ; i++) {
        if (length > byte_size[2 - i]) {
            int random_byte = rand() % (3 - i) ; 
            int pos = rand() % (length - byte_size[random_byte]) ;

            memcpy(arith_string, seed_input, seed_length) ;

            for(int n = 0 ; n < byte_size[random_byte] ; n++) {
                char c = seed_input[pos + n];  
                int byte = rand() % 71 + -35 ; 
                
                arith_string[pos + n] = (c + byte); 
            }
            arith_string[length] = 0x0 ; 
            break; 
        }
    }

    return length; 
}

int known_integer(char * integer_string, char * seed_input, int seed_length) {

    if (seed_input == NULL) return -1; 
    int length = seed_length ; 
    if (length == 0) return 0 ; 

    int byte_size[3] = {1, 2, 4} ; 
    int integer_list_size[3] = {9, 19, 27}; 

    for(int i = 0 ; i < 3; i++) {
        if (length > byte_size[2 - i]) { 
            int byte = rand() % (3 - i) ;
            int pos = rand() % (length - byte_size[byte]);  

            memcpy(integer_string, seed_input, seed_length); 

            int random_idx = rand() % integer_list_size[byte]; 
            if (byte == 0) {
                u_int8_t u8 = interesting_8[random_idx]; 
                integer_string[pos] = u8 ; 
            }else if (byte == 1) {
                u_int16_t u16 = interesting_16[random_idx]; 
                integer_string[pos] = u16; 
            }else if (byte == 2) {
                u_int32_t u32 = interesting_32[random_idx]; 
                integer_string[pos] = u32; 
            }
            break; 
        }
    }
    
    return length ;
}

int mutate(char * string, char * seed_input, int seed_length) {
    int (*mutator[6]) (char *, char *, int) = {
        delete_random_character, insert_random_character, bit_flip_random_character,
        byte_flip_random_character, byte_simple_arithmatic, known_integer
    }; 

    int choice = rand() % 6 ;
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