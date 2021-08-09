#include "../include/fuzzer.h"
#include "../include/file.h"
#include <signal.h>
#include <fcntl.h>
#define READ 0 
#define WRITE 1
#define TRUE 1 
#define FALSE 0 
int stdin_pipes[2]; 
int stdout_pipes[2]; 
int error_pipes[2]; 
int num_of_standard_out = 0 ; 
int num_of_error_returncode = 0 ;

void remove_result_files() {
    FILE * output_file = fopen("output", "r");
    if(output_file) {
        fclose(output_file);
        remove("output");
    }
    fclose(output_file);
    
    FILE * error_file = fopen("error", "r");
    if(error_file) {
        fclose(error_file);
        remove("error");
    }
    fclose(error_file);

    return ;
}

void subprocess_run(char *program, char* file) {
    char *buf = (char*)malloc(sizeof(char) * BUFF_MAX); 
    memset(buf, 0, BUFF_MAX);
    char *error = (char*)malloc(sizeof(char) * BUFF_MAX) ;
    memset(error, 0, BUFF_MAX); error[BUFF_MAX -1] = '\0';
    
    if( pipe(stdin_pipes) < 0 ) {
        perror("pipe error!\n");
        return ;
    }
    if(pipe(stdout_pipes) < 0) {
        perror("pipe error!\n");
        return ;
    }
    if(pipe(error_pipes) < 0) {
        perror("pipe error!\n");
        return ;
    }
    int pid = fork(); 
    if(pid < 0) {
        perror("fork error!\n");
    }else if(pid == 0){ 
        /* child */ 
        dup2(stdin_pipes[READ], 0) ;
        close(stdin_pipes[READ]); 
        close(stdin_pipes[WRITE]);

        close(stdout_pipes[READ]); 
        close(error_pipes[READ]); 
    
        dup2(stdout_pipes[WRITE], 1); 
        dup2(error_pipes[WRITE], 2); 

        execlp(program, program, file, 0x0);
    }else{ 
        /* parent */
        close(stdin_pipes[WRITE]);
        close(stdout_pipes[WRITE]); 
        close(error_pipes[WRITE]); 

        int status, stand_out_flag = FALSE, stand_err_flag = FALSE;
        ssize_t buff_output_size, buff_error_size; 
        wait(&status); 

        if(status != 0) {
            num_of_error_returncode++; 
        }

        FILE * f = fopen("output", "a"); 
        if (f == NULL) exit(1); 
        while((buff_output_size = read(stdout_pipes[READ], buf, BUFF_MAX - 1)) > 0) {
            if(!stand_out_flag) stand_out_flag = TRUE; 
            fwrite(buf, 1, buff_output_size, f);
        }
        if( stand_out_flag ) num_of_standard_out++; 
        
        fclose(f); 

        FILE * fp = fopen("error", "a"); 
        if (fp == NULL) exit(1); 
        while((buff_error_size = read(error_pipes[READ], error, BUFF_MAX - 1)) > 0 ) {
            fwrite(error, 1, buff_error_size, fp);
        }

        fclose(fp);

        close(stdout_pipes[READ]);
        close(error_pipes[READ]);
    }
}

void long_running_fuzzing() {
    char result[BUFF_MAX]; 
    int status, trials = 100; 
    FILE_INFO * f_info ; 

    srand(time(NULL)); 
 
    f_info = create_temp_dir(); 

    // 에러 파일 존재할 경우 삭제 
    remove_result_files(); 

    for(int i = 0 ; i < trials; i++) {
        char* basic_random = fuzzer(BASIC_LENGTH, BASIC_START, BASIC_RANGE); 
        int length = strlen(basic_random);
        basic_random = realloc(basic_random, length + 2); 
        basic_random[length] = '\n'; basic_random[length + 1] = '\0';  
        f_info = creating_input_file(f_info, basic_random); 
        
        subprocess_run("bc", f_info->path[i]); 
    }
    
    printf("Num of the standard output: %d\n", num_of_standard_out);
    printf("Num of the standard error: %d\n", trials - num_of_standard_out); 
    printf("Num of the error return code: %d\n", num_of_error_returncode); 
}

int main(void) {
    long_running_fuzzing(); 
}