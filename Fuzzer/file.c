#include "file.h"
#include <stdlib.h>
#include <stdio.h> 
#include <string.h>
#include <unistd.h>

int 
create_temp_dir(files_info_t * files_info) 
{
    char template[] = "tmp.XXXXXX"; 
    char * temporary_dir = mkdtemp(template); 

    if(temporary_dir == NULL) {
        perror("mkdtemp failed"); 
        return 0; 
    }

    files_info->dir_name = (char *)malloc(strlen(temporary_dir) + 1) ; 
    strcpy(files_info->dir_name, temporary_dir); 

    files_info->path = NULL; 
    files_info->count = 0;

    return 1; 
}

int 
make_filename(files_info_t * files_info)  
{
    // if (files_info->path == NULL) {
    //     files_info->path = (char **)malloc(sizeof(char *)) ; 
    // }else{
    //     files_info->path = (char **)realloc(files_info->count + 1, files_info->path) ;
    // }

    // files_info->path[files_info->count] = (char *)malloc(sizeof(char) * (strlen(files_info->dir_name) + 20));  //  /input1 (7)
    // sprintf(files_info->path[files_info->count] , "%s/output%d", files_info->dir_name, files_info->count); 
    // files_info->count++; 

    return 1; 
}