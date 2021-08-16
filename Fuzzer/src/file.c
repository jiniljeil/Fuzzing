#include "../include/file.h"
#include <stdlib.h>
#include <stdio.h> 
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int 
create_temp_dir(files_info_t * files_info) 
{
    char template[] = "tmp.XXXXXX"; 
    char * temporary_dir = mkdtemp(template); 

    if(temporary_dir == 0x0) {
        perror("mkdtemp failed"); 
        return 0; 
    }

    files_info->dir_name = (char *)malloc(strlen(temporary_dir) + 1) ; 
    strcpy(files_info->dir_name, temporary_dir); 

    files_info->path = NULL; 
    files_info->count = 0;

    return 1; 
}

char *
make_filename(files_info_t * files_info, int trial, int type)  
{
    if (files_info->path == NULL) {
        files_info->path = (char **)malloc(sizeof(char *)) ; 
    }else{
        files_info->path = (char **)realloc(files_info->path, (files_info->count + 1) * sizeof(char *)) ;
    }

    files_info->path[files_info->count] = (char *)malloc(sizeof(char) * (strlen(files_info->dir_name) + 20));  //  /output1 (8)
    if ( type == 0) {
        sprintf(files_info->path[files_info->count] , "%s/input%d", files_info->dir_name, trial);
    }else if (type == 1) {
        sprintf(files_info->path[files_info->count] , "%s/output%d", files_info->dir_name, trial);
    }else if (type == 2) {
        sprintf(files_info->path[files_info->count] , "%s/error%d", files_info->dir_name, trial);
    }

    files_info->count++;
    return files_info->path[files_info->count - 1]; 
}

int 
create_input_file(files_info_t * files_info, char * input, int input_length, int trial) 
{
    ssize_t input_size ;

    char * input_file = make_filename(files_info, trial, STDIN_FILENO) ;
    int input_fd = open(input_file, O_WRONLY | O_CREAT, 0644) ; 

    int sent = 0 ; 
    while(sent < input_length) {
        sent += write(input_fd, input, input_length - sent); 
    }

    if ( sent != input_length) { 
        perror("Write error!\n"); 
        return -1;
    }
    
    return 1; 
}

void 
files_info_free(files_info_t * files_info) {
    for(int i = 0 ; i < files_info->count; i++) {
        free(files_info->path[i]) ; 
    }
    free(files_info->path) ; 
    free(files_info->dir_name) ;
}

void 
remove_files_and_dir(files_info_t * files_info) {
    for(int i = 0 ; i < files_info->count; i++){
        if(remove(files_info->path[i]) == -1) {
            perror("rm failed: "); 
            return ;
        }
    }
    if(rmdir(files_info->dir_name) == -1) {
        perror("rmdir failed: "); 
        return ; 
    }
}