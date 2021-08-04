#include "fuzzer.h"
// Basic parameter (BASIC_LENGTH, BASIC_START, BASIC_RANGE) 
char * fuzzer(int max_length, int char_start, int char_range) {
    // 수정 필요 
    // srand(clock());
    int string_length = rand() % (max_length + 1 ); // '\0'
    char * out = (char*)malloc(sizeof(char) * string_length) ; 

    for(int i = 0 ; i < string_length; i++) {
        out[i] = (char) (char_start + rand() % char_range); 
    }
    
    return out; 
}

FILE_INFO* creating_input_files(char* random_string_by_fuzzer) {
    FILE_INFO *info = (FILE_INFO*)malloc(sizeof(FILE_INFO)); 

    char template[] = "tmp.XXXXXX"; 
    char *dir_name = mkdtemp(template); 

    if(dir_name == NULL) {
        perror("mkdtemp failed"); 
        return NULL; 
    }
    // PATH
    char * path = (char*)malloc(sizeof(char) * (strlen(dir_name) + 11)); 
    sprintf(path, "%s/%s", dir_name, "input.txt"); 

    // INPUT
    FILE * fp = fopen(path, "wb"); 
    fprintf(fp, "%s", random_string_by_fuzzer);
    fclose(fp); 

    fp = fopen(path, "rb"); 
    char * content = (char *)malloc(sizeof(char) * (strlen(random_string_by_fuzzer) + 1)); 
    fscanf(fp, "%[^\n]s", content); 

    printf("%s\n", content);

    fclose(fp);

    info->path = (char*)malloc(sizeof(char) * (strlen(path) + 1)); 
    info->dir_name = (char*)malloc(sizeof(char) * (strlen(dir_name) + 1)); 
    strcpy(info->path, path); 
    strcpy(info->dir_name, dir_name); 

    return info; 
}

void remove_files(FILE_INFO* f_info) {
    if(remove(f_info->path) == -1) {
        perror("rm failed: "); 
        return ;
    }
    if(rmdir(f_info->dir_name) == -1) {
        perror("rmdir failed: "); 
        return ; 
    }
}