
typedef struct files_info_t {
    char ** path ;
    char * dir_name ; 
    int count ;
} files_info_t ;

int create_temp_dir(files_info_t * files_info) ; 
int make_filename() ;