#include "../include/file.h"

FILE_INFO* create_temp_dir() {
    FILE_INFO *info = (FILE_INFO*)malloc(sizeof(FILE_INFO)); 
    char template[] = "tmp.XXXXXX"; 
    char * dir_name = mkdtemp(template); 

    if(dir_name == NULL) {
        perror("mkdtemp failed"); 
        return NULL; 
    }

    info->dir_name = (char*)malloc(sizeof(char) * (strlen(dir_name) + 1)); 
    strcpy(info->dir_name, dir_name); 
    info->path = NULL; 
    info->count = 0;
    return info; 
}

FILE_INFO* creating_input_file(FILE_INFO* info, char* random_string_by_fuzzer) {
    // PATH
    int buffer_size = strlen(random_string_by_fuzzer) + 1; 
    char * path = (char*)malloc(sizeof(char) * (strlen(info->dir_name) + 11)); 
    sprintf(path, "%s/input%d.txt", info->dir_name, info->count); 

    // INPUT
    FILE * fp = fopen(path, "wb"); 
    fwrite(random_string_by_fuzzer, 1, sizeof(char) * buffer_size, fp); 
    fclose(fp); 


    fp = fopen(path, "rb"); 
    char * content = (char *)malloc(sizeof(char) * buffer_size); 
    // fscanf(fp, "%[^\n]s", content); 
    fread(content, 1, sizeof(char) * buffer_size, fp);

    printf("%s\n", content);

    fclose(fp);

    if(info->path == NULL) {
        info->path = (char**)malloc(sizeof(char*)); 
    }else {
        info->path = (char**)realloc(info->path, sizeof(char*) * (info->count + 1)); 
    }

    info->path[info->count] = (char*)malloc(sizeof(char) * (strlen(path) + 1)); 
    strcpy(info->path[info->count], path); 

    info->count++;
    
    return info; 
}

void remove_files(FILE_INFO* f_info) {
    for(int i = 0 ; i < f_info->count; i++){
        if(remove(f_info->path[i]) == -1) {
            perror("rm failed: "); 
            return ;
        }
    }
    if(rmdir(f_info->dir_name) == -1) {
        perror("rmdir failed: "); 
        return ; 
    }
}