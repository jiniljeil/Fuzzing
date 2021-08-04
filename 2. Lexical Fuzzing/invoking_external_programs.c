#include "include/fuzzer.h"
#include "include/file.h"
#include <signal.h>
#define READ 0 
#define WRITE 1
int pipes[2]; 
int error_pipes[2]; 

void check_error_file() {
    FILE * error_file = fopen("error", "r");
    if(error_file) {
        fclose(error_file);
        remove(error);
    }
    fclose(error_file);
    return ;
}

void subprocess_run(char *program, char* file) {
    char *buf = (char*)malloc(sizeof(char) * BUFF_MAX); 
    memset(buf, 0, BUFF_MAX);
    char *error = (char*)malloc(sizeof(char) * BUFF_MAX) ;
    memset(error, 0, BUFF_MAX); 
    
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
    }else if(pid == 0){ // child
        close(pipes[READ]); 
        close(error_pipes[READ]); 

        dup2(pipes[WRITE], 0);
        dup2(pipes[WRITE], 1); 
        // close(pipes[WRITE]); 
        // dup2(pipes[WRITE], 2); 
        dup2(error_pipes[WRITE], 2); 

        execlp(program, program, file, 0x0);
        
    }else{ // parent
        int status; 
        wait(&status); 
        close(pipes[WRITE]); 
        close(error_pipes[WRITE]); 

        while(read(pipes[READ], buf, BUFF_MAX) > 0) {
            printf("%s\n", buf);
        }

        FILE * fp = fopen("error", "a"); 
        while(read(error_pipes[READ], error, BUFF_MAX) > 0 ) {
            printf("%s\n", error);
            fwrite(error, 1, strlen(error) + 1, fp);
        }
        fclose(fp);

        close(pipes[READ]);
        close(error_pipes[READ]);
    }
}

void long_running_fuzzing() {
    char result[BUFF_MAX]; 
    char* data = (char*)malloc(sizeof(char) * BUFF_MAX) ; data[0] = '\0'; 
    int _space = 1; // 1: 1024, 2: 2048, ..
    int status, trials = 100; 
    FILE_INFO * f_info ; 

    srand(time(NULL)); 
 
    f_info = create_temp_dir(); 

    // 에러 파일 존재할 경우 삭제 
    check_error_file(); 

    for(int i = 0 ; i < trials; i++) {
        char* basic_random = fuzzer(BASIC_LENGTH, BASIC_START, BASIC_RANGE); 

        f_info = creating_input_file(f_info, basic_random); 
        
        subprocess_run("bc", f_info->path[i]); 
    }
    if(strlen(data) != 0)  // '\0'
        printf("%s\n",data);

    remove_files(f_info); 
}

int main(void) {
    long_running_fuzzing(); 
}