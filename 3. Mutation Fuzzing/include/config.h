#ifndef CONFIG 
#define CONFIG 

#define PATH_MAX 4096 
#define MIN_LENGTH 10
#define MAX_LENGTH 100
#define CHAR_START 32
#define CHAR_RANGE 64
#define STDIN_INPUT 0 
#define CL_ARGUMENTS 1

typedef struct test_config {
    int trial ;

    int f_min_len ;
    int f_max_len ;
    int f_char_start ; 
    int f_char_range ;

    char seed_dir[PATH_MAX]; 
    int mutation_trial ; 

    int is_makefile; 
    int is_source ;  
    char * source_file ; 
    
    int input_method ;
    int num_of_cl_arguments ;

    char * binary_path ; 
    char ** cmd_args ; 
    int num_of_options ; 
    int timeout ;

    int (* oracle) (int, int) ;
} test_config_t ;

#endif