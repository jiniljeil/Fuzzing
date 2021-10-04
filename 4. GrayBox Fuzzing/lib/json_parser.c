#include "cJSON.h" 
#include <stdlib.h> 
#include <stdio.h> 
#define BUFF_SIZE 4096

void showItems(cJSON * json) { 
    int cJSON_array_size ; 
    cJSON * item = json; 
    if((cJSON_array_size = cJSON_GetArraySize(item)) != 0) {
        cJSON * ci ; 
        for (int i = 0 ; i < cJSON_array_size ; i++) {
            ci = cJSON_GetArrayItem(item, i) ;
            
            if (ci->string != NULL) {
                if (cJSON_HasObjectItem(item, ci->string)) { 
                    cJSON * obj_item = cJSON_GetObjectItemCaseSensitive(item, ci->string); 
                    printf("[item]:%s ", ci->string) ; 
                    if (obj_item != NULL && ci->valuestring != NULL) {
                        printf("[ValueString]: %s\n", ci->valuestring) ; 
                    }else {
                        printf("\n");
                    }
                }
            }
           
            showItems(ci); 
        }
    }  
}

int main(void) {
    char * text = (char *)malloc(sizeof(char) * BUFF_SIZE) ; 
    char c ; 
    int idx = 0, n = 1 ; 
    cJSON *json ; 
    
    while( (c = getchar()) != EOF) {
        if (idx >= BUFF_SIZE) { 
            text = (char *)realloc(text, sizeof(char) * BUFF_SIZE * (++n)) ;
        }
        text[idx++] = c; 
    }
    text[idx] = '\0'; 

    json = cJSON_Parse(text) ;
    if (!json) {
        printf("Error before: [%s]\n",cJSON_GetErrorPtr());
    } else { 
        printf("[JSON file structure]\n"); 
        if (cJSON_PrintPreallocated(json, text, idx, cJSON_True)) {
            printf("%s\n", cJSON_Print(json));
        }
        
        printf("<<< ITEMS >>>\n");
        showItems(json) ;   
    }

    cJSON * json_dup = cJSON_Duplicate(json, cJSON_True); 

    if (cJSON_Compare(json, json_dup, cJSON_False)) {
        printf("Copy is correct!\n"); 
    }
    cJSON_free(json_dup) ;

    /* Minify a strings, remove blank characters(such as ' ', '\t', '\r', '\n') from strings.*/
    cJSON_Minify(text); 
    json_dup = cJSON_Parse(text) ; 
    if (!json_dup) {
        printf("Error before: [%s]\n",cJSON_GetErrorPtr());
    }else {
        printf("%s\n", cJSON_PrintUnformatted(json_dup)); ;
    }

    if (cJSON_Compare(json, json_dup, cJSON_False)) {
        printf("Structure of minified text is same with the structure of original text!\n"); 
    }else{
        printf("Structure of minified text is not same with the structure of original text!\n");
    }

    /* Delete a cJSON entity and all subentities. */
    cJSON_Delete(json);
    cJSON_Delete(json_dup); 

    free(text); 

    return 0;
}


