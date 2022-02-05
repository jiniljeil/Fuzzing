#include "../include/schedule.h" 
#include <time.h> 
#include <stdlib.h>
#include <string.h> 
#include <stdio.h> 
#include <fcntl.h> 
#include <unistd.h>
#include <math.h> 
#define PATH_MAX 4096
int assign_energy(seed_t * seed_set, energy_set_t * energy_set, int * hash_table) {
    if (seed_set == NULL) return 0; 
    
    for (int i = 0 ; i < energy_set->num_of_seeds; i++) { 
        seed_set[i].energy = 1 / pow(hash_table[seed_set[i].path_id], 0.5);  
    }
    return 1; 
}

int normalized_energy(seed_t * seed_set, energy_set_t * energy_set) {
    if (seed_set == NULL || energy_set == NULL) return 0 ; 
    energy_set->sum_energy = 0 ; 
    // energy_set 
    for (int i = 0 ; i < energy_set->num_of_seeds ; i++) {
        energy_set->seed_energy_set[i] = seed_set[i].energy; 
        // energy sum 
        energy_set->sum_energy += energy_set->seed_energy_set[i] ; 
    }

    for (int i = 0 ; i < energy_set->num_of_seeds ;i++) { 
        energy_set->normal_energy_set[i] = (double) (energy_set->seed_energy_set[i]) * 100 / energy_set->sum_energy ; 
    } 
    return 1; 
}

int probability_random_choice(energy_set_t * energy_set) {
    double random_n = (double) rand() / RAND_MAX; // (0 ~ 1) 
    double probability = random_n * 100.0f; // ( 0.0 % ~ 100.0%)
    double cumulative = 0.0f ; // 누적 합  

    for (int i = 0 ; i < energy_set->num_of_seeds ;i++) {
        cumulative += energy_set->normal_energy_set[i]; 
        if (probability < cumulative) {
            return i ;
        }
    }
    return energy_set->num_of_seeds - 1 ;
}

int seed_choose(char * seed_input, seed_t * seed_set, energy_set_t * energy_set, int * seed_idx, int * hash_table) {
    if (seed_input == NULL || seed_set == NULL) return 0;
    
    if (assign_energy(seed_set, energy_set, hash_table) && normalized_energy(seed_set, energy_set)) { 
        *seed_idx = probability_random_choice(energy_set); 
        if (*seed_idx >= 0 && *seed_idx < energy_set->num_of_seeds) {
            memcpy(seed_input, seed_set[*seed_idx].seed_input, BUFF_SIZE); 
            return seed_set[*seed_idx].length ; 
        }
    }
    return 0;
}

int add_seed_file(char * seed_dir, seed_t * seed_set, int * num_of_seed_files, char * input, int input_len) {
    char path[PATH_MAX]; 
    ssize_t size = 0 ; 

    int path_length = sprintf(path, "%s/seed%d", seed_dir, *num_of_seed_files); 
    path[path_length] = 0x0; 

    strcpy(seed_set[*num_of_seed_files].seed_input, path); 
    seed_set[*num_of_seed_files].length = input_len; 
    seed_set[*num_of_seed_files].energy = 1; 

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
    if (fd != -1) close(fd); 
    return (++*num_of_seed_files); 
}