
typedef struct files_info_t {
    char ** path ;  // input, output, error 
    char * dir_name ; 
    int count;
} files_info_t ;

int create_temp_dir(files_info_t * files_info) ; 
char * make_filename(files_info_t * files_info, int trial, int type); 
void files_info_free(files_info_t * files_info) ; 
void remove_files_and_dir(files_info_t * files_info); 
int create_input_file(files_info_t * files_info, char * input, int input_length, int trial) ;