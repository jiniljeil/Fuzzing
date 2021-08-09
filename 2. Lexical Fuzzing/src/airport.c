#include "../include/airport.h"

/* code means key of dictioary named airports_codes */
int code_repOK(char* code) {
    int code_length = strlen(code); 
    assert(code_length == 3) ;
    for(int i = 0 ; i < code_length; i++) {
        assert(isalpha(code[i]) > 0); 
        assert(isupper(code[i]) > 0); 
    }
    return 1; 
}

int airport_codes_repOK(DICT* airport_codes) { 
    for(int i = 0 ; i < airport_codes->size; i++) {
        assert(code_repOK(airport_codes->item[i]->key) == 1);
    }
    return 1; 
}

void add_new_airport(DICT* airport_codes, char* code, char* city) {
    assert(code_repOK(code)); 
    assert(airport_codes_repOK(airport_codes));
    dict_item_add(airport_codes, code, city); 
    assert(airport_codes_repOK(airport_codes));
}