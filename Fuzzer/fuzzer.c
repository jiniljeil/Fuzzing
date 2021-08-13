#include "fuzzer.h" 
#include <stdlib.h> 
#include <unistd.h>
#include <stdio.h> 
#include <fcntl.h>
#include <string.h>
#include <time.h>
#define READ 0
#define WRITE 1 
#define BUFF_SIZE 1024
/*
1. check some conditions
    - binary path validity
    - default values
2. make result directory
*/
static test_config_t config ; 

void
config_init(test_config_t * config_p) 
{
    config_p->fuzz_arg.f_min_len = MIN_LENGTH ;
    config_p->fuzz_arg.f_max_len = MAX_LENGTH ;
    config_p->fuzz_arg.f_char_start = CHAR_START ; 
    config_p->fuzz_arg.f_char_range = CHAR_RANGE ; 

    config_p->prog_arg.binary_path = NULL ;
    config_p->prog_arg.timeout = 2; 
    config_p->prog_arg.cmd_args = NULL ; 
    config_p->prog_arg.num_of_options = 0 ;

    config_p->trial = 10; 
    config_p->oracle = NULL ; 
}

void 
config_copy(test_config_t * config_p) {
    config.fuzz_arg.f_min_len = config_p->fuzz_arg.f_min_len;
    config.fuzz_arg.f_max_len = config_p->fuzz_arg.f_max_len; 
    config.fuzz_arg.f_char_start = config_p->fuzz_arg.f_char_start ; 
    config.fuzz_arg.f_char_range = config_p->fuzz_arg.f_char_range ;

    int path_length = strlen(config_p->prog_arg.binary_path); 

    if( path_length > PATH_MAX ) {
        perror("Path is the longest! The max length of path is 4096.\n"); 
        return ;
    }else{
        config.prog_arg.binary_path = (char *)malloc(sizeof(char) * (path_length + 1)) ; 
        strcpy(config.prog_arg.binary_path, config_p->prog_arg.binary_path);
    }
    
    config.prog_arg.timeout = config_p->prog_arg.timeout; 
    config.prog_arg.num_of_options = config_p->prog_arg.num_of_options; 

    if(config_p->prog_arg.cmd_args != NULL) {
        if (config_p->prog_arg.num_of_options == 0) {
            perror("Please specify the num of options.\n");
            return ;
        }else{
            config.prog_arg.cmd_args = (char **)malloc(sizeof(char *) * (config.prog_arg.num_of_options + 2)) ; 

            config.prog_arg.cmd_args[0] = (char *)malloc(sizeof(char) * (path_length + 1)) ;
            strcpy(config.prog_arg.cmd_args[0], config.prog_arg.binary_path);

            for(int i = 1 ; i <= config.prog_arg.num_of_options; i++) {
                int length = strlen(config_p->prog_arg.cmd_args[i]) + 1; 
                config.prog_arg.cmd_args[i] = (char *)malloc(sizeof(char) * length) ; 
                strcpy(config.prog_arg.cmd_args[i], config_p->prog_arg.cmd_args[i]) ;
            }
            config.prog_arg.cmd_args[config.prog_arg.num_of_options] = NULL; 
        }
    }else{
        config.prog_arg.cmd_args = (char **)malloc(sizeof(char *) * 2); 
        config.prog_arg.cmd_args[0] = (char *)malloc(sizeof(char) * (path_length + 1)); 
        strcpy(config.prog_arg.cmd_args[0], config.prog_arg.binary_path); 
        config.prog_arg.cmd_args[1] = NULL; 
    }

    config.trial = config_p->trial;
    config.oracle = config_p->oracle; 
}

void
fuzzer_init (test_config_t * config_p)
{
    config_copy(config_p); 

    // check whether the file exists or not.
	if (config_p != NULL && config.prog_arg.binary_path != NULL && access(config.prog_arg.binary_path, X_OK) != -1 ) {
        if (config.fuzz_arg.f_min_len < 0) config.fuzz_arg.f_min_len = MIN_LENGTH; 
        if (config.fuzz_arg.f_max_len < 0) config.fuzz_arg.f_max_len = MAX_LENGTH; 

        if (config.fuzz_arg.f_char_start < 0 || config.fuzz_arg.f_char_start > 127) config.fuzz_arg.f_char_start = CHAR_START; 
        if (config.fuzz_arg.f_char_range < 0 || (config.fuzz_arg.f_char_start + config.fuzz_arg.f_char_range) > 127) config.fuzz_arg.f_char_range = CHAR_RANGE; 

        if (config.fuzz_arg.f_min_len > config.fuzz_arg.f_max_len) {
            config.fuzz_arg.f_max_len = config.fuzz_arg.f_min_len; 
        }
    }else{
        perror("The path is incorrect!\n"); 
        exit(1); 
    }
}

int 
run(char * input, int length, files_info_t * files_info)
{   
    
    int status = -1 ;
    int stdin_pipes[2]; 
    int stdout_pipes[2];
    int stderr_pipes[2]; 
    
    if(pipe(stdin_pipes) < 0 || pipe(stdout_pipes) < 0 || pipe(stderr_pipes) < 0) {
        perror("pipe error!\n");
        exit(1); 
    }   

    int pid = fork(); 

    if(pid < 0) {
        perror("fork failed!\n"); 
        exit(1) ;
    }else if (pid == 0) {
        /* child */
        close(stdout_pipes[READ]); 
        close(stderr_pipes[READ]);
        
        write(stdin_pipes[WRITE], input, length); 
        dup2(stdin_pipes[READ], 0); 

        close(stdin_pipes[READ]);
        close(stdin_pipes[WRITE]); 
       
        dup2(stdout_pipes[WRITE], 1);
        dup2(stderr_pipes[WRITE], 2); 

        execv(config.prog_arg.binary_path, config.prog_arg.cmd_args); 
        printf("The process execute error!\n") ; 
        exit(1); 
    }else {
        /* parent */
        close(stdin_pipes[READ]); 
        close(stdin_pipes[WRITE]); 
        close(stdout_pipes[WRITE]); 
        close(stderr_pipes[WRITE]); 

        ssize_t stdout_size, stderr_size; 
        
        wait(&status); 

        char std_out[BUFF_SIZE] ; 
        char std_err[BUFF_SIZE] ;

        // make_filename(&files_info_t) ;

        while( (stdout_size = read(stdout_pipes[READ], std_out, BUFF_SIZE)) > 0) {
            std_out[stdout_size] = '\0';
            printf("TEST:%s\n", std_out); 
        }
        
        while( (stderr_size = read(stderr_pipes[READ],  std_err, BUFF_SIZE)) > 0) {
            printf("%s\n", std_err); 
        }

        close(stdout_pipes[READ]); 
        close(stderr_pipes[READ]); 
    }
    return status; 
}   

void 
fuzzer_main ()
{
    files_info_t files_info ;
    // create_temp_dir(&files_info) ;
    srand(time(0));
    
    for (int i = 0; i < config.trial; i++) {
    	char * input = (char *)malloc(sizeof(char) * (config.fuzz_arg.f_max_len + 1)); 
        int input_len = create_input(&config, input) ; 

    	run(input, input_len, &files_info) ; 
    	// oracle(config) ; // file....

        free(input) ;
    }
}
