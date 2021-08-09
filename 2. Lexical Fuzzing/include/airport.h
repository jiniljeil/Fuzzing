#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

int code_repOK(char* code) ; 
int airport_codes_repOK(DICT* airport_codes); 
void add_new_airport(DICT* airport_codes, char* code, char* city); 