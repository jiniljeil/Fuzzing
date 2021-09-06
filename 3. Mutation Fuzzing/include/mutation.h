
int store_seed_files(char * seed_dir, char * storage[]);
int add_seed_file(char * seed_dir, char * new_seed_input[], int * num_of_seed_files, char * input, int input_len) ; 
int delete_random_character(char * deleted_string, char * seed_input, int seed_length) ; 
int insert_random_character(char * inserted_string, char * seed_input, int seed_length) ; 
int flip_random_character(char * flip_string,char * seed_input, int seed_length) ; 
int mutate(char * string, char * seed_input, int seed_length ) ;
int mutate_input(char * input, char * seed_file_storage[] , int order, int mutation); 