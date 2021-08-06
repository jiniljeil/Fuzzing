#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include "../include/dictionary.h"
// #define ASSERT_EXAMPLE

void make_items(DICT * dict_name) {
    dict_item_add(dict_name, "YVR", "Vancouver"); 
    dict_item_add(dict_name, "JFK", "New York-JFK"); 
    dict_item_add(dict_name, "CDG", "Paris-Charles de Gaulle"); 
    dict_item_add(dict_name, "CAI", "Cairo"); 
    dict_item_add(dict_name, "LED", "St. Petersburg"); 
    dict_item_add(dict_name, "PEK", "Beijing"); 
    dict_item_add(dict_name, "HND", "Tokyo-Haneda"); 
    dict_item_add(dict_name, "AKL", "Auckland"); 
}

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

void airport_code_check(DICT * airport_codes) {
    // AIRPORT CODE CHECK 
    printf("Airport_codes_repOK(): %s\n", (airport_codes_repOK(airport_codes) == 1) ? "True" : "False");
    
#ifdef ASSERT_EXAMPLE
    dict_item_add(airport_codes, "YMML", "Melbourne"); 

    // AIRPORT CODE CHECK 
    printf("Airport_codes_repOK(): %s\n", (airport_codes_repOK(airport_codes) == 1) ? "True" : "False");
#endif

    add_new_airport(airport_codes, "BER", "Berlin");

#ifdef ASSERT_EXAMPLE
    add_new_airport(airport_codes, "London-Heathrow", "LHR");
#endif

    add_new_airport(airport_codes, "IST", "Istanbul Yeni Havalimanı");

}

void program_specific_checkers() {
    DICT * airport_codes = dictionary_init() ; 
    make_items(airport_codes);

    for(int i = 0 ; i < airport_codes->size; i++) {
        printf("%s\n", dict_find(airport_codes, airport_codes->item[i]->key));
    }

    airport_code_check(airport_codes) ; 

    dict_free(airport_codes);
}

int main(void) {
    program_specific_checkers();
    return 0;
}