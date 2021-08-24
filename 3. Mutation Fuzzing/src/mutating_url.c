#include "../include/mutating_url.h"
#include <assert.h> 
#include <regex.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

int http_program(char * url) {
    regex_t regex; 
    regmatch_t regmatch[7] ; 
    int length = 0 ; 
    url_t * url_info = (url_t*)malloc(sizeof(url_t)) ; 

    char * info[] = {url_info->scheme, url_info->netloc, url_info->path, url_info->port, url_info->query, url_info->fragment}; 

    // http://www.google.com/search:8080?q=fuzzing&p=f#ddd
    // Pattern: ^(http|https):\/\/([a-zA-Z0-9\.]+)(\/[^\:^\?]*)?(\:[0-9]+)?(\?[a-zA-Z0-9\&\=]+)?\#?(.*)
    char * pattern = "^(http|https):\\/\\/([a-zA-Z0-9\\.]+)(\\/[^\\:^\\?]*)\?(\\:[0-9]+)?(\\\?[a-zA-Z0-9\\&\\=]+)?\\#\?(.*)"; 
    
    printf("%s\n", pattern); 

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) { 
        fprintf(stderr,"This URL is not matched from URL format."); 
        return 0; 
    } 

    if ( regexec(&regex, url, 7, regmatch, 0) != 0) {
        fprintf(stderr, "Error: regex execute failed!\n"); 
        return 0; 
    } 

    for(int i = 0 ; i < 6; i++) {
        length = regmatch[i+1].rm_eo - regmatch[i+1].rm_so;
        info[i] = (char *)malloc(sizeof(char) * (length + 1)) ; 
        memcpy(info[i], url + regmatch[i+1].rm_so, length); 
        info[i][length] = 0x0; 
        printf("%s\n", info[i]); 
    }


    return 1; 
}

int is_valid_url(char * url) {
    int result = http_program(url); 
    assert(result == 1); 
    return 1; 
}

int main(void) {
    is_valid_url("http://www.google.com/search:8080?q=fuzzing&p=f#ddd"); 
}
