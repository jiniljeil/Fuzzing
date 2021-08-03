#include <stdio.h>
#include <time.h> 
#include <unistd.h>
#include <stdlib.h> 
#include <string.h> 

#define BASIC_LENGTH 100
#define BASIC_START 32
#define BASIC_RANGE 32

// Basic parameter (BASIC_LENGTH, BASIC_START, BASIC_RANGE) 
char * fuzzer(int max_length, int char_start, int char_range) {

    // 수정 필요 
    srand(time(NULL)); 

    int string_length = rand() % (max_length + 1);
    char * out = (char*)malloc(sizeof(char) * string_length) ; 

    for(int i = 0 ; i < string_length; i++) {
        out[i] = (char) (char_start + rand() % char_range); 
    }

    return out; 
}

void creating_input_files(char* random_string_by_fuzzer) {
    char template[] = "tmp.XXXXXX"; 
    char *dir_name = mkdtemp(template); 

    if(dir_name == NULL) {
        perror("mkdtemp failed"); 
        return ; 
    }

    char * path = (char*)malloc(sizeof(char) * (strlen(dir_name) + 1)); 
    strcpy(path, dir_name);
    strcat(path, "/"); 
    strcat(path, "input.txt"); 
 
    // INPUT
    FILE * fp = fopen(path, "wb"); 
    fprintf(fp, "%s", random_string_by_fuzzer);
    fclose(fp); 

    fp = fopen(path, "rb"); 
    char * content = (char *)malloc(sizeof(char) * (strlen(random_string_by_fuzzer) + 1)); 
    fscanf(fp, "%[^\n]s", content); 
    fclose(fp);

    printf("CONTENT: %s\n", content); 
    if(remove(path) == -1) {
        perror("rm failed: "); 
        return ;
    }
    if(rmdir(dir_name) == -1) {
        perror("rmdir failed: "); 
        return ; 
    }
}

int main(void) {
    char* basic_random = fuzzer(BASIC_LENGTH, BASIC_START, BASIC_RANGE); 
    printf("BASIC: %s\n", basic_random) ;

    creating_input_files(basic_random); 


    return 0;
}