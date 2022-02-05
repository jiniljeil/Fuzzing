#include "../include/fuzzer.h" 
#include "../include/whitebox.h" 
#include "../include/mutation.h"
#include <stdlib.h> 
#include <unistd.h>
#include <stdio.h> 
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/time.h>
#include <signal.h>
#include <sys/wait.h> 
#include <assert.h> 
#define READ 0
#define WRITE 1 
#define BUFF_SIZE 1024
// #define TROFF_RESULT  
#define PRINT_COVERAGE
#define PRINT_COVERAGE_CASE1

// #define PRINT_COVERAGE_CASE2

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

    config_p->mutation_trial = 1; 

    config_p->num_of_source_files = 0 ;
    for(int i = 0 ; i < MAX_NUM_SOURCES ; i++) config_p->source_file[i] = NULL;
    strcpy(config_p->working_dir, "./") ; 
    config_p->seed_dir[0] = '\0'; 

    config_p->input_method = STDIN_INPUT ;
    config_p->num_of_cl_arguments = 0 ;
    
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

    int path_length = 0 ;

    config.f_min_len = config_p->f_min_len;
    config.f_max_len = config_p->f_max_len; 
    config.f_char_start = config_p->f_char_start ; 
    config.f_char_range = config_p->f_char_range ;
    
    config.mutation_trial = config_p->mutation_trial; 

    if ( strlen(config_p->seed_dir) == 0 ) { 
        config.input_generator = RANDOM ; 
    } else {
        strncpy(config.seed_dir, config_p->seed_dir, PATH_MAX) ;
        config.input_generator = MUTATION ; 
    }
    
    strncpy(config.working_dir, config_p->working_dir, PATH_MAX) ; 
    
    // SOURCE FILE -> Coverage compile 
    config.num_of_source_files = config_p->num_of_source_files ;
    
    int source_file_length[MAX_NUM_SOURCES] = {0} ;
    // Check whether the source filename is entered. 
    if ( config.num_of_source_files > 0){  
        for(int i = 0 ; i < config.num_of_source_files ; i++) {
            if (config_p->source_file[i] != NULL) {
                    config.source_file[i] = (char *)malloc(sizeof(char) * PATH_MAX) ; 
                // realpath 
                if ( realpath(config_p->source_file[i], config.source_file[i]) == 0x0 ) {
                    perror("Error: realpath returns NULL!\n") ; 
                    exit(1); 
                }   
                source_file_length[i] = strlen(config.source_file[i]); 
            }
        }
    }

    for(int i = 0 ; i < config.num_of_source_files ; i++) {
        if ( source_file_length[i] > PATH_MAX) {
            perror("Path is the longest! The max length of path is 4096.\n"); 
            return ;
        }
    }

    // EXECUTABLE FILE PATH
    path_length = strlen(config_p->binary_path); 

    if( path_length > PATH_MAX ) {
        perror("Path is the longest! The max length of path is 4096.\n"); 
        return ;
    }else{
        config.binary_path = (char *)malloc(sizeof(char) * (path_length + 1)) ; 
        strcpy(config.binary_path, config_p->binary_path);
    }

    config.input_method = config_p->input_method ;
    config.num_of_cl_arguments = config_p->num_of_cl_arguments ;

    config.timeout = config_p->timeout; 
    config.num_of_options = config_p->num_of_options; 

    // Check whether the option exists
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
        // COMMAND LINE ARGUMENT
        if (config.input_method == CL_ARGUMENTS) {
            config.cmd_args = (char **)malloc(sizeof(char *) * (config.num_of_cl_arguments + 2)); 
            config.cmd_args[0] = (char *)malloc(sizeof(char) * (path_length + 1)); 
            strcpy(config.cmd_args[0], config.binary_path); 
            
            for (int i = 1 ; i <= config.num_of_cl_arguments; i++) {
                config.cmd_args[i] = (char *)malloc(sizeof(char) * BUFF_SIZE); 
            }
            
            config.cmd_args[config.num_of_cl_arguments + 1] = NULL; 
        // STANDARD INPUT
        }else{
            config.cmd_args = (char **)malloc(sizeof(char *) * 2); 
            config.cmd_args[0] = (char *)malloc(sizeof(char) * (path_length + 1)); 
            strcpy(config.cmd_args[0], config.binary_path); 
            config.cmd_args[1] = NULL; 
        }
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

    if (config.mutation_trial < 1) {
        fprintf(stderr, "Fuzzer init: Please set the number of mutation trial more than 0.!\n"); 
        exit(1); 
    }
    
    if (config.input_method != STDIN_INPUT && config.input_method != CL_ARGUMENTS) {
        fprintf(stderr, "Fuzzer init: it has the input methods are STDIN_INPUT and CL_ARGUMENTS.\n"); 
        exit(1); 
    }

    if (config.input_method == CL_ARGUMENTS && config.num_of_cl_arguments == 0) {
        fprintf(stderr, "Fuzzer init: Please set the number of command line arguments!\n") ;
        exit(1); 
    }

    if ((config.num_of_source_files > MAX_NUM_SOURCES)) {
        fprintf(stderr, "Fuzzer init: Please set the number of source files less than 32(MAX_NUM_SOURCES)\n"); 
        exit(1) ;
    }

    for (int i = 0 ; i < config.num_of_source_files ; i++) {
        if (config.source_file[i] == 0x0) {
            perror("Fuzzer init: The number of source files does not match with the number of entered source files!\n"); 
            exit(1); 
        }
        if (access(config.source_file[i], R_OK) == -1) { 
            perror("Fuzzer init: Source filepath is incorrect!\n"); 
            exit(1); 
        }
    }

    if ((config.binary_path != 0x0 && access(config.binary_path, X_OK) != -1)) {
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

int create_input(char * input) { 
    int length = rand() % (config.f_max_len - config.f_min_len + 1) + config.f_min_len ;
    
    for (int i = 0; i < length; i++) {
        input[i] = rand() % (config.f_char_range + 1) + config.f_char_start ;
    }
    input[length] = 0x0 ;

    return length ;
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
        alarm(config.timeout);

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
    close(fd); 
}

void 
config_free() 
{
    if (config.binary_path != NULL) free(config.binary_path) ;
    for(int i = 0 ; i < config.num_of_source_files ; i++) {
        if (config.source_file[i] != NULL) free(config.source_file[i]) ;
    }

    for(int i = 0 ; i < config.num_of_options + 2; i++) {
        if (config.cmd_args[i] != NULL) free(config.cmd_args[i]); 
    }

    free(config.cmd_args); 
}

void 
energy_set_free(energy_set_t * energy_set) {
    if (energy_set->seed_energy_set != NULL) free(energy_set->seed_energy_set); 
    if (energy_set->normal_energy_set != NULL) free(energy_set->normal_energy_set); 
    if (energy_set != NULL) free(energy_set); 
}

int 
get_input(char * input, int len, int trial) 
{ 
    char path[PATH_MAX];
    ssize_t size = 0;

    sprintf(path, "%s/input%d", p_files_info->dir_name, trial); 

    int fd = open(path, O_RDONLY) ; 
    
    if (fd == -1) {
        perror("Cannot open input file\n"); 
        return -1; 
    }

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
print_each_of_trial_coverage(coverset_t * coverage_sets) 
{
    printf("---------------Covearge Dataset---------------\n"); 
    for(int i = 0; i < config.trial ; i++) {
        printf("Trial[%d] (%d): ", i + 1, coverage_sets->coverage_set[i]); 
        for(int j = 0 ; j < coverage_sets->coverage_set[i]; j++) {
            printf("#"); 
        }
        printf("\n");
    }
}

void 
print_coveage_result(coverset_t * coverage_sets, int num_of_source_lines, int num_of_lines, int num_of_branch_lines) 
{

#ifdef PRINT_COVERAGE_CASE1
    
    printf("---------------Union Coverage---------------\n");
    
    for(int i = 0 ; i < num_of_source_lines ; i++) {
        if (coverage_sets->union_coverage_set[i] == '1') {
            printf("%d ", i); 
            coverage_sets->num_of_total_coverage++; 
        }
        if (coverage_sets->union_branch_coverage_set[i] == '1') {
            coverage_sets->num_of_total_branch_coverage++; 
        }
    }

    printf("\nThe number of max coverage of specific line : %d / %d (%.2f %%)\n", coverage_sets->num_of_max_coverage, num_of_lines, (float)coverage_sets->num_of_max_coverage * 100/ num_of_lines); 
    printf("The number of total covered lines : %d / %d (%.2f %%)\n", coverage_sets->num_of_total_coverage, num_of_lines, (float)coverage_sets->num_of_total_coverage * 100 / num_of_lines); 
    printf("The number of total covered branches : %d / %d (%.2f %%)\n", coverage_sets->num_of_total_branch_coverage, num_of_branch_lines, (float)coverage_sets->num_of_total_branch_coverage * 100 / num_of_branch_lines); 
    printf("--------------------------------------------\n"); 

#endif 

#ifdef PRINT_COVERAGE_CASE2

    FILE * fp = fopen("CoverageResult", "a"); 

    if( fp == NULL) {
        perror("Error: file open failed!\n"); 
        exit(1); 
    }else{

    }
    for(int i = 0 ; i < num_of_source_lines ; i++) {
        if (coverage_sets->union_coverage_set[i] == '1') {
            fprintf(fp, "%d ", i); 
            coverage_sets->num_of_total_coverage++; 
        }
    }
    fprintf(fp, "\nThe number of total covered lines : %d\n", coverage_sets->num_of_total_coverage); 
    fclose(fp) ;
#endif
}

void 
fuzzer_summary(result_t * results) 
{ 
    double total_execute_time = 0.0f; 
    int num_of_pass = config.trial, num_of_fail = 0, num_of_unresolved = 0 ; 
    
    for (int i = 0 ; i < config.trial ;i++) {
        total_execute_time += results[i].exec_time ; 
        if ( !strcmp(results[i].test_result, "FAILED") ) {
            num_of_fail++; 
        } else if ( !strcmp(results[i].test_result, "UNRESOLVED")) {
            num_of_unresolved++; 
        }
    }
    num_of_pass = config.trial - num_of_fail - num_of_unresolved ; 
    printf("--------------Test Result--------------\n"); 
    printf("Trial: %10d \n", config.trial); 
    printf("Execute Time: %.6f \n", total_execute_time); 
    printf("PASS: %11d (%6.2f %%)\n", num_of_pass, (double) num_of_pass * 100 / config.trial); 
    printf("FAILED: %9d (%6.2f %%)\n", num_of_fail, (double) num_of_fail * 100 / config.trial) ; 
    printf("UNSOLVED: %7d (%6.2f %%)\n", num_of_unresolved, (double) num_of_unresolved * 100 / config.trial) ;
    printf("---------------------------------------\n");
}

void 
write_data_in_csv(coverset_t * coverset, int num_of_source_lines) 
{ 
    int fd = open("TestResult.csv", O_CREAT | O_WRONLY | O_APPEND, 0644) ;  

    if ( fd == -1 ) { 
        fprintf(stderr, "Error: cannot write the data on the TestResult file!\n"); 
        return ;
    }

    unsigned int num_of_branch_coverages = 0 ; 

    for (int i = 0 ; i < num_of_source_lines ; i++) {
        if ( coverset->union_branch_coverage_set[i] == '1')  {
            num_of_branch_coverages++; 
        }
    }
    
    char result[32] ; 
    sprintf(result, "%d\n", num_of_branch_coverages); 
    write(fd, result, strlen(result)); 
    
    close(fd); 
}

void remove_test_result() {
    if( access("TestResult.csv", F_OK) != -1 ) {
        if (remove("TestResult.csv") != 0) { 
            perror("Error: file remove failed!\n"); 
            return ;
        }
    }
}   

void 
fuzzer_main (test_config_t * config_p)
{   
    clock_t start, end ; 
    files_info_t files_info ;
    coverset_t coverage_sets[MAX_NUM_SOURCES] ; 

    int new_branch = false; 
    files_info.count = 0;
    p_files_info = &files_info; 

    fuzzer_init(config_p) ; 
    create_temp_dir(&files_info) ;
    // remove_test_result(); 
    srand(time(0)); 

    char * storage[4096]; 
    int num_of_seed_files = store_seed_files(config.seed_dir, storage); 

    for(int i = 0 ; i < config.num_of_source_files ; i++) {
        if (config.num_of_source_files > 0 && config.source_file[i] != NULL) {
            coverage_sets[i].coverage_set = (int*)malloc(sizeof(int) * config.trial); 
            coverage_sets[i].num_of_total_coverage = 0 ; 
            coverage_sets[i].num_of_max_coverage = 0 ;
            coverage_sets[i].num_of_total_branch_coverage = 0 ;
        }
    }
    
    /* 
        Time out setting 
    */
    signal(SIGALRM, timout_handler); 

    result_t * results = (result_t *)malloc(sizeof(result_t) * config.trial); 
    
    char * c_file[MAX_NUM_SOURCES] = { NULL } ;
    char gcov_file[PATH_MAX]; 
    int num_of_source_lines[MAX_NUM_SOURCES] = {0,};
    int num_of_lines[MAX_NUM_SOURCES] = {0,}; // line coverage 
    int num_of_branch_lines[MAX_NUM_SOURCES] = {0,}; // branch coverage 

    int ret = chdir(config.working_dir);  

    if (ret != 0) { 
        perror("Failed change working directory\n"); 
    }

    for(int i = 0 ; i < config.num_of_source_files ; i++) {
        if (config.num_of_source_files > 0 && config.source_file[i] != NULL) {
            c_file[i] = remove_slash(config.source_file[i], strlen(config.source_file[i]) - 1); 

            // "#####" of gcov file counts
            if (create_gcov(config.source_file[i]) != 0) {
                perror("Error: the gcov file does not make!\n"); 
            }

            if ( c_file[i] != NULL) {
                sprintf(gcov_file, "%s.gcov", c_file[i]); 
                num_of_source_lines[i]= num_of_total_lines(config.source_file[i]);  
                num_of_lines[i] = num_of_uncovered_lines(gcov_file); 
                num_of_branch_lines[i] = num_of_uncovered_branch_lines(gcov_file); 
            }

            memset(coverage_sets[i].union_coverage_set, '0', num_of_lines[i]);
            memset(coverage_sets[i].union_branch_coverage_set , '0', num_of_branch_lines[i]); 
        }
    }
    
    // Get the number of total source code lines, uncovered lines, and uncovered branch.
    char * input = (char *)malloc(sizeof(char) * (BUFF_SIZE)); 
    int input_len = 0 ; 
    seed_t * seed_set = (seed_t *)malloc(sizeof(seed_t) * SEED_MAX) ; 
    
    if ( load_seed_inputs(seed_set, storage, num_of_seed_files) == -1) { 
        printf("SEED LOAD ERROR!\n"); 
        exit(1); 
    } 
    
    for(int i = 0 ; i < num_of_seed_files ; i++) free(storage[i]);  

    // Allocation of energy set
    energy_set_t * energy_set = (energy_set_t *)malloc(sizeof(energy_set_t)); 
    energy_set->seed_energy_set = (int *)malloc(sizeof(int) * SEED_MAX); 
    energy_set->normal_energy_set = (double *)malloc(sizeof(double) * SEED_MAX); 
    energy_set->num_of_seeds = num_of_seed_files ; 
    
    unsigned short hash_value = 0 ; 
    int seed_idx = 0 ; 
    int hash_table[65537] ;  // 2^16   
    memset(hash_table, 0, sizeof(hash_table)) ;
    for (int i = 0; i < config.trial; i++) {
        new_branch = false; 
        start = clock(); 
        
        if ( i >= num_of_seed_files ) {
            if ( config.input_generator == RANDOM ) {
            input_len = create_input(input) ; 
            } else if ( config.input_generator == MUTATION ) {
                input_len = mutate_input(input, seed_set, energy_set, config.mutation_trial, &seed_idx, hash_table); 
            }
        }else { 
            strncpy(input, seed_set[i].seed_input, seed_set[i].length); 
            input[seed_set[i].length] = 0x0 ;
            input_len = seed_set[i].length ; 
        }

        create_input_file(&files_info, input, input_len, i + 1);

        // Copy the input
        if (config.input_method == CL_ARGUMENTS && config.num_of_cl_arguments > 0) {
            for(int j = 1 ; j <= config.num_of_cl_arguments; j++) {
                memcpy(config.cmd_args[j], input, input_len); 
            }
        }

    	int returncode = run(input, input_len, &files_info, i + 1) ; 
        test_oracle_run(&results[i], returncode, i + 1) ; 

        if ( config.num_of_source_files > 0) { 
            for(int n = 0 ; n < config.num_of_source_files ; n++) {
                if (config.source_file[n] != NULL) { 
                    if (c_file[n] != NULL && create_gcov(config.source_file[n]) != 0 ) {
                        perror("Error: the gcov file does not make!\n"); 
                    }
                    sprintf(gcov_file, "%s.gcov", c_file[n]); 
                    int cov_num_of_lines = read_gcov_coverage(gcov_file, &coverage_sets[n], i, &hash_value) ;     
                    coverage_sets[n].num_of_max_coverage = (coverage_sets[n].num_of_max_coverage < cov_num_of_lines) ? cov_num_of_lines : coverage_sets[n].num_of_max_coverage ;
                    printf("HASH: %d\n", hash_value); 
                    if (hash_table[hash_value] < 1) {
                        new_branch = true; // To add the new seed. 
                        hash_table[hash_value] = 1 ;
                    } else { 
                        hash_table[hash_value]++; 
                    }
                    write_data_in_csv(coverage_sets, num_of_source_lines[n]) ; 
                }
            }
        }

        end = clock(); 

        results[i].exec_time = (double)(end - start) / CLOCKS_PER_SEC ;

        if (config.num_of_source_files > 0) {
            for(int n = 0 ; n < config.num_of_source_files ; n++) {
                if (config.source_file[n] != NULL) remove_the_gcda_file(config.source_file[n]);
            }
        }

        // When the mutated input is found
        if (i >= num_of_seed_files) {
            if (new_branch == true ) {
                if ( add_seed_file(config.seed_dir, seed_set, &num_of_seed_files, input, input_len) == -1 ) { 
                    perror("Cannot add the seed input in the directory!\n"); 
                }
                new_branch = false; 
                seed_set[num_of_seed_files - 1].path_id = hash_value ; 
            } 
        }else { 
            seed_set[seed_idx].path_id = hash_value; 
        }
    }

    free(input) ;

#ifdef PRINT_COVERAGE
    if (config.num_of_source_files > 0) { 
        for(int i = 0 ; i < config.num_of_source_files; i++) {
            if (config.source_file[i] != NULL) {
                // print_each_of_trial_coverage(&coverage_sets) 
                printf("\nSOURCE FILE: %s\n", config.source_file[i]); 
                print_coveage_result(&coverage_sets[i], num_of_source_lines[i], num_of_lines[i], num_of_branch_lines[i]);

                sprintf(gcov_file, "%s.gcov", c_file[i]); 
                if( access(gcov_file, F_OK) != -1 ) {
                    if (remove(gcov_file) != 0) { 
                        perror("Error: file remove failed!\n"); 
                        return ;
                    }
                }
            }
        }
    }
#endif 

    fuzzer_summary(results) ;

    int fd = open("TestResult.csv", O_CREAT | O_WRONLY | O_APPEND, 0644) ;  

    if ( fd == -1 ) { 
        fprintf(stderr, "Error: cannot write the data on the TestResult file!\n"); 
        return ;
    }
    write(fd, "\n", 1); 
#ifdef FILE_REMOVE 
    // remove the output and error files
    remove_files_and_dir(&files_info); 
#endif
    for(int i = 0 ; i < config.num_of_source_files ; i++) {
        if (c_file[i] != NULL) free(c_file[i]); 
        if (coverage_sets[i].coverage_set != NULL) free(coverage_sets[i].coverage_set);
    }
    
    if (results != NULL) free(results);
    energy_set_free(energy_set) ;
    files_info_free(&files_info);  
    config_free(); 
    if (seed_set != NULL) free(seed_set);
}
