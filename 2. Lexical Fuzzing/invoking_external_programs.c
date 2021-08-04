#include "include/fuzzer.h"
#include <unistd.h>
#include <signal.h>
#define READ 0 
#define WRITE 1
int pipes[2]; 
int error_pipes[2]; 
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

        while(read(error_pipes[READ], error, BUFF_MAX) > 0 ) {
            printf("%s\n", error);
        }

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

    for(int i = 0 ; i < trials; i++) {
        char* basic_random = fuzzer(BASIC_LENGTH, BASIC_START, BASIC_RANGE); 

        f_info = creating_input_file(f_info, basic_random); 
        
        subprocess_run("bc", f_info->path[i]); 
        // char* command = (char*)malloc(sizeof(char) * (strlen(f_info->path[i]) + 1 + 3)); // path strlen + \0(1) + "bc "(3)
        // sprintf(command, "cat %s | bc 2>> error", f_info->path[i]);  // cat filename | bc 

        // FILE * fp = popen(command, "r");
        // if(fp == NULL) return ; 

        // // fscanf(fp, "%s", result); 
        // fread(result, sizeof(result), 1, fp); 

        // status = pclose(fp);

        // if(status == -1) {
        //     perror("The subprocess is exited incorrectly!\n"); 
        //     return ; 
        // }else{
        //     printf("exit status %d\n", status); 
        // }

        // if(strlen(data) > BUFF_MAX * _space) { 
        //     data = (char*)realloc(data, (++_space) * BUFF_MAX); 
        // }else{
        //     strcat(data, result); 
        // }

    }
    if(strlen(data) != 0)  // '\0'
        printf("%s\n",data);

    remove_files(f_info); 
}

int main(void) {
    long_running_fuzzing(); 
}