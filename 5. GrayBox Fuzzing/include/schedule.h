#ifndef SCHEDULE 
#define SCHEDULE
#define SEED_MAX 4096 
#define BUFF_SIZE 1024 

typedef struct seed { 
    char seed_input[BUFF_SIZE] ; 
    int length ; 
    int energy ; 
} seed_t ; 

typedef struct energy_set { 
    int * seed_energy_set; 
    int sum_energy ; 
    int num_of_seeds; 
    double * normal_energy_set ;   
} energy_set_t ; 

int assign_energy(seed_t * seed_set, energy_set_t * energy_set); 
int normalized_energy(seed_t * seed_set, energy_set_t * energy_set) ;
int probability_random_choice(energy_set_t * energy_set); 
int seed_choose(char * seed_input, seed_t * seed_set, energy_set_t * energy_set);
#endif 