#ifndef SCHEDULE 
#define SCHEDULE
#define SEED_MAX 4096 
#define BUFF_SIZE 1024 

typedef struct seed { 
    char seed_input[BUFF_SIZE] ; 
    int length ; 
    int energy ; 
    unsigned short path_id ; // hash value 
} seed_t ; 

typedef struct energy_set { 
    int * seed_energy_set; 
    int sum_energy ; 
    int num_of_seeds; 
    double * normal_energy_set ;   
} energy_set_t ; 

int assign_energy(seed_t * seed_set, energy_set_t * energy_set, int * hash_table); 
int add_seed_file(char * seed_dir, seed_t * new_seed_input, int * num_of_seed_files, char * input, int input_len) ; 
int normalized_energy(seed_t * seed_set, energy_set_t * energy_set) ;
int probability_random_choice(energy_set_t * energy_set); 
int seed_choose(char * seed_input, seed_t * seed_set, energy_set_t * energy_set, int * seed_idx, int * hash_table) ; 
#endif 