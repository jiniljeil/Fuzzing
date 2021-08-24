#include "../include/muating_url.h"
#include <assert.h> 
#include <regex.h> 
#include <stdio.h> 

int http_program(char * url) {
    regex_t regex; 
    regmatch_t regmatch[6] ; 
    // http://www.google.com/search:8080?q=fuzzing&p=f#ddd
    // Pattern: ^(http|https):\/\/([a-zA-Z0-9\.]+)\/?([^\:]*)\:?([0-9]+)\??([a-zA-Z0-9\&\=]+)\#?(.*)
    char * pattern = "^(http|https):\\/\\/([a-zA-Z0-9\\.]+)\\/\?([^\\:]*)\\:\?([0-9]+)\\\?\?([a-zA-Z0-9\\&\\=]+)\\#\?(.*)";

    if (regcomp(url, pattern, REG_EXTENDED) != 0) { 
        fprintf(stderr,"This URL is not matched from URL format."); 
        return 0; 
    } 

    return 1; 
}

int is_valid_url(char * url) {
    int result = http_program(url); 
    assert(result == 1); 
    return 1; 
}
