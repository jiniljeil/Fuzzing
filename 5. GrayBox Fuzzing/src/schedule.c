#include "../include/schedule.h" 
#include <time.h> 
#include <stdlib.h>
#include <string.h> 
#include <stdio.h> 
int assign_energy(seed_t * seed_set, energy_set_t * energy_set) {
    if (seed_set == NULL) return 0; 
    
    for (int i = 0 ; i < energy_set->num_of_seeds; i++) seed_set[i].energy = 1 ; 
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

int seed_choose(char * seed_input, seed_t * seed_set, energy_set_t * energy_set) {
    if (seed_input == NULL || seed_set == NULL) return 0;
    
    if (assign_energy(seed_set, energy_set) && normalized_energy(seed_set, energy_set)) { 
        int seed_idx = probability_random_choice(energy_set); 
        if (seed_idx >= 0 && seed_idx < energy_set->num_of_seeds) {
            memcpy(seed_input, seed_set[seed_idx].seed_input, BUFF_SIZE); 
            return seed_set[seed_idx].length ; 
        }
    }
    return 0;
}