#include "../include/url_parser.h"
#include <assert.h> 
#include <regex.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

int url_parser(char * url, url_t * url_info) {
    regex_t regex; 
    regmatch_t regmatch[7] ; 
    int length = 0 ; 

    char * info[] = {url_info->scheme, url_info->netloc, url_info->path, url_info->port, url_info->query, url_info->fragment}; 

    // http://www.google.com/search:8080?q=fuzzing&p=f#ddd
    // Pattern: ^(http|https)\:\/\/([a-zA-Z0-9\.]+)(\/[^\:^\?]*)?(\:[0-9]+)?(\?[a-zA-Z0-9\&\=]+)?\#?(.*)
    char * pattern = "^(http|https)\\:\\/\\/([a-zA-Z0-9\\.]+)(\\/[^\\:^\\?]*)\?(\\:[0-9]+)?(\\\?[a-zA-Z0-9\\&\\=]+)?\\#\?(.*)"; 

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) { 
        return -1; 
    } 

    if ( regexec(&regex, url, 7, regmatch, 0) != 0) {
        return -1; 
    } 

    for(int i = 0 ; i < 6; i++) {
        length = regmatch[i+1].rm_eo - regmatch[i+1].rm_so;
        info[i] = (char *)malloc(sizeof(char) * (length + 1)) ; 
        memcpy(info[i], url + regmatch[i+1].rm_so, length); 
        info[i][length] = 0x0; 
    }

    return 1 ;
}

int http_program(char * url) {
    url_t * url_info = (url_t*)malloc(sizeof(url_t)) ; 
    int ret = url_parser(url, url_info); 
    return ret; 
}

int is_valid_url(char * url) {
    int result = http_program(url); 
    assert(result == 1); 
    return 1; 
}