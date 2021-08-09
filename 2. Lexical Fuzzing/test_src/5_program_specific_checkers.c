#include <stdio.h>
#include "../include/airport.h"
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