#include "include/fuzzer.h"
#include "include/file.h"
#include <signal.h>
#include <fcntl.h>
#define READ 0 
#define WRITE 1
int pipes[2]; 
int error_pipes[2]; 
int num_of_error_returncode = 0;
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
    
    if(pipe(pipes) < 0) {
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
        close(pipes[READ]); 
        close(error_pipes[READ]); 

        int devnull = open("/dev/null", O_RDONLY); 
        dup2(devnull, 0); 
        dup2(pipes[WRITE], 1); 
        dup2(error_pipes[WRITE], 2); 

        execlp(program, program, file, 0x0);
        
    }else{ 
        /* parent */
        int status;
        ssize_t buff_output_size, buff_error_size; 
        wait(&status); 

        if(status != 0) {
            num_of_error_returncode++; 
        }

        close(pipes[WRITE]); 
        close(error_pipes[WRITE]); 

        FILE * f = fopen("output", "a"); 
        if (f == NULL) exit(1); 
        while((buff_output_size = read(pipes[READ], buf, BUFF_MAX - 1)) > 0) {
            fwrite(buf, 1, buff_output_size, f);
        }
        fclose(f); 

        FILE * fp = fopen("error", "a"); 
        if (fp == NULL) exit(1); 
        while((buff_error_size = read(error_pipes[READ], error, BUFF_MAX - 1)) > 0 ) {
            fwrite(error, 1, buff_error_size, fp);
        }
        fclose(fp);

        close(pipes[READ]);
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

        f_info = creating_input_file(f_info, basic_random); 
        
        subprocess_run("bc", f_info->path[i]); 
    }
    
    printf("Num of the error return code: %d\n", num_of_error_returncode); 
}

int main(void) {
    long_running_fuzzing(); 
}