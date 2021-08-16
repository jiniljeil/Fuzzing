#include "../include/fuzzer.h" 
#include <stdlib.h> 
#include <unistd.h>
#include <stdio.h> 
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/time.h>
#include <signal.h>
#define READ 0
#define WRITE 1 
#define BUFF_SIZE 1024
// #define FILE_REMOVE
/*
1. check some conditions
    - binary path validity
    - default values
2. make result directory
*/

static test_config_t config ; 
int pid ;  // store the pid to kill the process when the timeout is occured. 
files_info_t * p_files_info; 
/*
    Default config initialization 
*/
void
config_init(test_config_t * config_p) 
{
    config_p->f_min_len = MIN_LENGTH ;
    config_p->f_max_len = MAX_LENGTH ;
    config_p->f_char_start = CHAR_START ; 
    config_p->f_char_range = CHAR_RANGE ; 

    config_p->binary_path = NULL ;
    config_p->timeout = 2; 
    config_p->cmd_args = NULL ; 
    config_p->num_of_options = 0 ;

    config_p->trial = 10; 
    config_p->oracle = NULL ; 
}

/*
    When the number of options is different from config->num_of_options, return -1. 
*/
int 
check_num_of_options(test_config_t * config_p) 
{
    int num_of_options = 0 ; 
    while(config_p->cmd_args[num_of_options] != 0x0) {
        num_of_options++; 
    }

    if (config_p->num_of_options != num_of_options) {
        perror("The number of options is different from the number of entered options "); 
        return -1; 
    }
    return 0 ;
}

/*
    Copy the config entered by user to avoid the direct reference.
*/
void 
config_copy(test_config_t * config_p) 
{
    if (config_p == 0x0) {
        perror("Config init: NULL\n") ; 
        exit(1); 
    }

    config.f_min_len = config_p->f_min_len;
    config.f_max_len = config_p->f_max_len; 
    config.f_char_start = config_p->f_char_start ; 
    config.f_char_range = config_p->f_char_range ;

    int path_length = strlen(config_p->binary_path); 

    if( path_length > PATH_MAX ) {
        perror("Path is the longest! The max length of path is 4096.\n"); 
        return ;
    }else{
        config.binary_path = (char *)malloc(sizeof(char) * (path_length + 1)) ; 
        strcpy(config.binary_path, config_p->binary_path);
    }
    
    config.timeout = config_p->timeout; 
    config.num_of_options = config_p->num_of_options; 

    if(config_p->cmd_args != NULL) {
        if (check_num_of_options(config_p) == -1) {
            perror("Please specify the num of options.\n");
            return ;
        }else{
            /*
                When the user adds the option 
            */
            config.cmd_args = (char **)malloc(sizeof(char *) * (config.num_of_options + 2)) ; 

            config.cmd_args[0] = (char *)malloc(sizeof(char) * (path_length + 1)) ;
            strcpy(config.cmd_args[0], config.binary_path);

            for(int i = 0 ; i < config.num_of_options; i++) {
                int length = strlen(config_p->cmd_args[i]) + 1; 
                config.cmd_args[i+1] = (char *)malloc(sizeof(char) * length) ; 
                strcpy(config.cmd_args[i+1], config_p->cmd_args[i]) ;
            }
            config.cmd_args[config.num_of_options + 1] = NULL; 
        }
    }else{
        config.cmd_args = (char **)malloc(sizeof(char *) * 2); 
        config.cmd_args[0] = (char *)malloc(sizeof(char) * (path_length + 1)); 
        strcpy(config.cmd_args[0], config.binary_path); 
        config.cmd_args[1] = NULL; 
    }

    config.trial = config_p->trial;
    config.oracle = config_p->oracle; 
}

/*  
    Test Oracle 
*/
int 
default_test_oracle(int returncode, int trial) 
{
    if (returncode == 0) return 0; 
    else return returncode ; 
}

// TODO
void 
test_oracle_run(result_t * result, int returncode, int trial) 
{
    result->returncode = returncode ; 
    int ret_code = config.oracle(returncode, trial); 
    result->test_result = (returncode == 0) ? "PASS" : (returncode < 0) ? "FAIL" : "UNRESOLVED" ; 
}

/*
    Copy the config entered by user, check whether the path exists or not.  
*/
void
fuzzer_init (test_config_t * config_p)
{
    config_copy(config_p); 

    if (config.binary_path != 0x0 && access(config.binary_path, X_OK) != -1 ) {
        if (config.f_min_len < 0) {
            fprintf(stderr, "Fuzzer init: The minimum length of random string must be greater than zero.\n"); 
            exit(1); 
        }
        if (config.f_max_len < 0) {
            fprintf(stderr, "Fuzzer init: The maximum length of random string must be greater than zero.\n"); 
            exit(1); 
        }

        if (config.f_min_len > config.f_max_len) {
            fprintf(stderr, "Fuzzer init: The maximum length of random string must be greater than the minimum length of random string.\n"); 
            exit(1);
        }

        if (config.f_char_start < 0 || config.f_char_start > 255) {
            fprintf(stderr, "Fuzzer init: The start of ASCII character is between 0 and 255.\n"); 
            exit(1); 
        }

        if (config.f_char_range < 0 || (config.f_char_start + config.f_char_range) > 255) {
            fprintf(stderr, "Fuzzer init: The range of ASCII character is between 0 and 255.\n"); 
            exit(1); 
        }
        
        if (config.trial < 0) {
            fprintf(stderr, "Fuzzer init: The value of trials must be greater than zero.");
        } 

        if (config.oracle == 0x0) {
            config.oracle = default_test_oracle ;
        }
    }else{
        perror("Fuzzer init: entered the path is incorrect!\n"); 
        exit(1); 
    }
}

/*
    Time handler: If the test program exceeds setted the time, calls this function. 
*/
void 
timout_handler(const int signal) 
{
    if (signal == SIGALRM) {
        fprintf(stderr, "Time out! (%d seconds)\n", config.timeout);    
        int exit_proc = kill(pid, SIGINT) ;
        if (exit_proc != 0) {
            perror("Kill error!\n"); 
            exit(1);  
        }
    }
}

/*
    Give standard input on the program, and write the standard output and error on the file in the temporary directory. 
*/
int 
run(char * input, int length, files_info_t * files_info, int num)
{   
    int status = -1 ;
    int stdin_pipes[2]; 
    int stdout_pipes[2];
    int stderr_pipes[2]; 
    
    if(pipe(stdin_pipes) < 0 || pipe(stdout_pipes) < 0 || pipe(stderr_pipes) < 0) {
        perror("Pipe error!\n");
        exit(1); 
    }   

    pid = fork(); 

    if(pid < 0) {
        perror("Fork failed!\n"); 
        exit(1) ;
    }else if (pid == 0) {
        /* 
            Give the standard input on the program, execute the program. 
        */
        close(stdout_pipes[READ]); 
        close(stderr_pipes[READ]);
        
        write(stdin_pipes[WRITE], input, length); 
        dup2(stdin_pipes[READ], 0); 

        close(stdin_pipes[READ]);
        close(stdin_pipes[WRITE]); 
       
        dup2(stdout_pipes[WRITE], 1);
        dup2(stderr_pipes[WRITE], 2); 

        execv(config.binary_path, config.cmd_args); 
        printf("The process execute error!\n") ; 
        exit(1); 
    }else {
        close(stdin_pipes[READ]); 
        close(stdin_pipes[WRITE]); 
        close(stdout_pipes[WRITE]); 
        close(stderr_pipes[WRITE]); 

        ssize_t stdout_size, stderr_size; 
        
        wait(&status); 

        char std_out[BUFF_SIZE] ; 
        char std_err[BUFF_SIZE] ;

        /*
            Read standard output from standard output pipe, write on the output file. 
        */
        char * output_file = make_filename(files_info, num, STDOUT_FILENO) ;
        int output_fd = open(output_file, O_WRONLY | O_CREAT, 0644) ; 

        while( (stdout_size = read(stdout_pipes[READ], std_out, BUFF_SIZE)) > 0) {
            write(output_fd, std_out, stdout_size); 
        }
        
        /*
            Read standard error from standard error pipe, write on the error file. 
        */
        char * error_file = make_filename(files_info, num, STDERR_FILENO) ; 
        int error_fd = open(error_file, O_WRONLY | O_CREAT, 0644); 

        while( (stderr_size = read(stderr_pipes[READ], std_err, BUFF_SIZE)) > 0) {
            write(error_fd, std_err, stderr_size); 
        }

        close(stdout_pipes[READ]); 
        close(stderr_pipes[READ]); 
        close(output_fd); 
        close(error_fd); 
    }
    return status; 
}   

void 
print_result(files_info_t * files_info, result_t * result, int num) 
{

    int fd;
    ssize_t stdout_size = 0, stderr_size = 0, w_stdout_size = 0, w_stderr_size = 0; 
    char stdout_result[BUFF_SIZE]; 
    char stderr_result[BUFF_SIZE]; 

    memset(stdout_result, 0, sizeof(stdout_result)) ;
    memset(stderr_result, 0, sizeof(stderr_result)) ;

    printf("(CompletedProcess(program=\'%s\', args=\'", config.binary_path); 
    
    for(int i = 0; i < config.num_of_options; i++) {
        if ( i == config.num_of_options - 1) printf("%s", config.cmd_args[i+1]);
        else printf("%s ", config.cmd_args[i+1]); 
    }
    
    printf("\',  returncode=%d, stdout=\'", result->returncode); 

    fflush(stdout);
    /*
        Standard output  
    */ 
    fd = open(files_info->path[ 3 * num + 1], O_RDONLY); 

    while((stdout_size = read(fd, stdout_result, BUFF_SIZE - 1)) > 0) {
        w_stdout_size = write(1, stdout_result, stdout_size) ;
        if (w_stdout_size != stdout_size) perror("Standard output: write error!\n");
    }   

    printf("\', stderr=\'"); 
    close(fd); 

    /*
        Standard error 
    */
    fflush(stdout) ; 

    fd = open(files_info->path[ 3 * num + 2], O_RDONLY); 

    while((stderr_size = read(fd, stderr_result, BUFF_SIZE - 1)) > 0) {
        w_stderr_size = write(1, stderr_result, stderr_size) ;
        if (w_stderr_size != stderr_size) perror("Standard error: write error!\n");
    }

    printf("\'), %s)\n", result->test_result); 
}

void 
config_free() 
{
    free(config.binary_path) ;
    for(int i = 0 ; i < config.num_of_options + 2; i++) {
        free(config.cmd_args[i]); 
    }
    free(config.cmd_args); 
}

int 
get_input(char * input, int len, int trial) 
{ 
    char path[PATH_MAX];
    ssize_t size = 0;

    sprintf(path, "%s/input%d", p_files_info->dir_name, trial); 

    int fd = open(path, O_RDONLY) ; 
    // 수정 필요 
    if ((size += read(fd, input, len)) > 0) {
        input[size] = '\0'; 
    }

    close(fd); 

    return size ;
} 

int 
get_output(char * output, int len, int trial) 
{
    char path[PATH_MAX];
    ssize_t size = 0 ;
    sprintf(path, "%s/output%d", p_files_info->dir_name, trial); 

    int fd = open(path, O_RDONLY) ; 
    // 수정 필요 
    if ((size += read(fd, output, len)) > 0) {
        output[size] = '\0'; 
    }
    close(fd); 
    return size; 
}

int 
get_error(char * error, int len, int trial) 
{
    char path[PATH_MAX];
    ssize_t size = 0 ;
    sprintf(path, "%s/error%d", p_files_info->dir_name, trial); 

    int fd = open(path, O_RDONLY) ; 
    // 수정 필요 
    if ((size += read(fd, error, len)) > 0) {
        error[size] = '\0'; 
    }
    close(fd); 
    return size; 
}

void 
fuzzer_summary(result_t * results)  
{   
    int no_backslash_cnt = 0, no_8bit_failure_cnt = 0, no_dot_failure_cnt = 0; 
    for(int i = 0 ; i < config.trial ; i++) {
        if (results[i].returncode == 256) {
            no_backslash_cnt++; 
        }else if (results[i].returncode == 512) {
            no_8bit_failure_cnt++; 
        }else if (results[i].returncode == 768) {
            no_dot_failure_cnt++; 
        }
    }

    printf("---------------Fuzzer Summary---------------\n"); 
    printf("1. no_backslash_d(\\D): %d\n", no_backslash_cnt) ; 
    printf("2. no_8bit: %d\n", no_8bit_failure_cnt); 
    printf("3. no_dot: %d\n", no_dot_failure_cnt); 
    printf("4. normal case: %d\n", config.trial - no_backslash_cnt - no_8bit_failure_cnt - no_dot_failure_cnt) ;
    printf("--------------------------------------------\n"); 
}

void 
fuzzer_main (test_config_t * config)
{
    files_info_t files_info ;
    p_files_info = &files_info; 

    fuzzer_init(config) ; 

    create_temp_dir(&files_info) ;
    srand(time(0)); 
    
    /* 
        Time out setting 
    */
    signal(SIGALRM, timout_handler); 

    result_t * results = (result_t *)malloc(sizeof(result_t) * config->trial); 

    for (int i = 0; i < config->trial; i++) {
        alarm(config->timeout);

    	char * input = (char *)malloc(sizeof(char) * (config->f_max_len + 1)); 

        int input_len = create_input(config, input) ; 

        create_input_file(&files_info, input, input_len, i + 1);

    	int returncode = run(input, input_len, &files_info, i + 1) ; 

        test_oracle_run(&results[i], returncode, i + 1) ; 

        print_result(&files_info, &results[i], i); 
    	
        free(input) ;
    }

    fuzzer_summary(results) ;

#ifdef FILE_REMOVE 
    // remove the output and error files
    remove_files_and_dir(&files_info); 
#endif
    free(results); 
    files_info_free(&files_info); 
    config_free(); 
}