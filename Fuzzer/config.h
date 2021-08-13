#ifndef CONFIG 
#define CONFIG 

#define PATH_MAX 4096 
#define MIN_LENGTH 10
#define MAX_LENGTH 100
#define CHAR_START 32
#define CHAR_RANGE 64

typedef struct test_config {
    int trial ;

    int f_min_len ;
    int f_max_len ;
	int f_char_start ; 
    int f_char_range ;

    char * binary_path ; 
	char ** cmd_args ; // >> -b : case 1 / @ : case 2 / @@ : case 3 ?
    int num_of_options ; 
    int timeout ;

    int (* oracle) (char * dir_name) ;
} test_config_t ;

#endif