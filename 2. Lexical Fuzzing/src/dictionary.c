
#include "../include/dictionary.h"
#include <stdlib.h>
#include <stdio.h>
DICT * dictionary_init() {
    DICT* dict = (DICT*)malloc(sizeof(DICT)) ; 
    dict->size = 0 ;
    dict->item = NULL ;

    return dict;
}

char* dict_find(DICT * dict_name, char* key) {

    for(int i = 0 ; i < dict_name->size; i++) {
        if(!strcmp(dict_name->item[i]->key, key)) {
            return dict_name->item[i]->value; 
        }
    }

    return NULL;
}

int dict_key_contains(DICT * dict_name, char* key) {
    for(int i = 0 ; i < dict_name->size; i++) {
        if(!strcmp(dict_name->item[i]->key, key)) {
            return 1; 
        }
    }
    return 0;
}

void dict_item_add(DICT * dict_name, char* key, char* value) {
    if (dict_name->item == NULL) { 
        dict_name->item = (DICT_ITEM**)malloc(sizeof(DICT_ITEM*));
    }
    dict_name->item = (DICT_ITEM **)realloc(dict_name->item, sizeof(DICT_ITEM*) * (dict_name->size + 1));

    dict_name->item[dict_name->size] = (DICT_ITEM*)malloc(sizeof(DICT_ITEM));
    dict_name->item[dict_name->size]->key = (char*)malloc(sizeof(char) * (strlen(key) + 1)); 
    dict_name->item[dict_name->size]->value = (char*)malloc(sizeof(char) * (strlen(value) + 1)); 

    strcpy(dict_name->item[dict_name->size]->key, key);
    strcpy(dict_name->item[dict_name->size]->value, value); 

    dict_name->item[dict_name->size]->key[strlen(key)] = '\0'; 
    dict_name->item[dict_name->size]->value[strlen(value)] = '\0';

    dict_name->size++;
}   

void dict_free(DICT * dict_name) {
    for(int i = 0 ; i < dict_name->size; i++) {
        free(dict_name->item[i]->key);
        free(dict_name->item[i]->value); 
        free(dict_name->item[i]); 
    }
    free(dict_name->item) ;
    free(dict_name);
}