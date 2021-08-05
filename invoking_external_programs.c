#include "include/fuzzer.h"
#include "include/file.h"
#include <signal.h>
#include <fcntl.h>
#define READ 0 
#define WRITE 1
int pipes[2]; 
int error_pipes[2]; 

void check_error_file() {
    FILE * error_file = fopen("error", "r");
    if(error_file) {
        fclose(error_file);
        remove("error");
    }
    fclose(error_file);
    return ;
}

void subprocess_run(char *program, char* file, FILE_INFO * error_file_info) {
    int file_num = 0 ;
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
        char error_info_filename[16]; 
        wait(&status); 
        printf("exit status %d\n", status);
        close(pipes[WRITE]); 
        close(error_pipes[WRITE]); 
        
        sprintf(error_info_filename, "%s/error%d.txt", error_file_info->dir_name, file_num); 
        printf("TEST %s %s\n", error_file_info->dir_name, error_info_filename);
        file_num++;
        FILE * f = fopen(error_info_filename, "a"); 

        while(read(pipes[READ], buf, BUFF_MAX - 1) > 0) {
            printf("%s\n", buf);
        }

        // FILE * fp = fopen("error", "a"); 
        while(read(error_pipes[READ], error, BUFF_MAX - 1) > 0 ) {
            fwrite(error, 1, strlen(error), f);
        }
        fclose(f);

        close(pipes[READ]);
        close(error_pipes[READ]);
    }
}

void long_running_fuzzing() {
    char result[BUFF_MAX]; 
    char* data = (char*)malloc(sizeof(char) * BUFF_MAX) ; data[0] = '\0'; 
    int _space = 1; // 1: 1024, 2: 2048, ..
    int status, trials = 100; 

    srand(time(NULL)); 
 
    FILE_INFO * f_info = create_temp_dir(); 
    FILE_INFO * output_file_info = create_temp_dir(); 

    // 에러 파일 존재할 경우 삭제 
    // check_error_file(); 

    for(int i = 0 ; i < trials; i++) {
        char* basic_random = fuzzer(BASIC_LENGTH, BASIC_START, BASIC_RANGE); 

        f_info = creating_input_file(f_info, basic_random); 
        
        subprocess_run("bc", f_info->path[i], output_file_info); 
    }
    if(strlen(data) != 0)  // '\0'
        printf("%s\n",data);

    // remove_files(f_info); 
}

int main(void) {
    long_running_fuzzing(); 
}