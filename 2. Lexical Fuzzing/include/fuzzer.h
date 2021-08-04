#include <stdio.h>
#include <time.h> 
#include <stdlib.h> 
#include <string.h> 
#define BASIC_LENGTH 100
#define BASIC_START 32
#define BASIC_RANGE 32
#define DEBUG


// generate random string by fuzzer 
char * fuzzer(int max_length, int char_start, int char_range); 
