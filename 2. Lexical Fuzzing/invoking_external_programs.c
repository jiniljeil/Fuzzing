#include "fuzzer.h"

void long_running_fuzzing() {
    char result[BUFF_MAX]; 
    char* data = (char*)malloc(sizeof(char) * BUFF_MAX) ; data[0] = '\0'; 
    int _space = 1; // 1: 1024, 2: 2048, ..
    int status, trials = 100; 

    srand(time(NULL)); 
    for(int i = 0 ; i < trials; i++) {
        char* basic_random = fuzzer(BASIC_LENGTH, BASIC_START, BASIC_RANGE); 
        strcat(basic_random, "\n");
        FILE_INFO * f_info = creating_input_files(basic_random); 
        
        char* command = (char*)malloc(sizeof(char) * (strlen(f_info->path) + 1 + 3)); // path strlen + \0(1) + "bc "(3)
        sprintf(command, "cat %s | bc 2>> error", f_info->path);  // cat filename | bc 

        FILE * fp = popen(command, "r");
        if(fp == NULL) return ; 

        fscanf(fp, "%s", result); 

        status = pclose(fp);

        if(status == -1) {
            perror("The subprocess is exited incorrectly!\n"); 
            return ; 
        }else{
            printf("exit status %d\n", status); 
        }
        if(strlen(data) > BUFF_MAX * _space) { 
            data = (char*)realloc(data, (++_space) * BUFF_MAX); 
        }else{
            strcat(data, result); 
        }

        remove_files(f_info); 
    }
}

int main(void) {
    long_running_fuzzing(); 
}