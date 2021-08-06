#include <string.h> 

typedef struct dict_item {
    char *key ;
    char *value ; 
} DICT_ITEM; 

typedef struct dict_list {
    int size; 
    DICT_ITEM ** item; 
} DICT ;

DICT * dictionary_init(); 
char* dict_find(DICT * dict_name, char* key) ; 
void dict_item_add(DICT * dict_name, char* key, char* value) ; 
void dict_free(DICT * dict_name) ;
int dict_key_contains(DICT * dict_name, char* key); 