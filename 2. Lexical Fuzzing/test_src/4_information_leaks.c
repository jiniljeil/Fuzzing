#include "../include/simpleFuzzer.h"
#include <assert.h>
#define BUFF_SIZE 2048

// C substring function definition
char* substring(char *str, int start_idx, int end_idx) {
    int string_length = strlen(str);

    if( string_length < end_idx || string_length < start_idx ) {
        perror("Out of bound memory access error\n"); 
        return NULL; 
    }

    char* sub_str = (char*)malloc(sizeof(char) * ((end_idx - start_idx + 1) + 1)); 
    int idx = 0; 
    while(idx <= end_idx) {
        sub_str[idx] = str[start_idx + idx]; 
        idx++;
    }

    sub_str[idx] = '\0';

    return sub_str; 
}

char* make_secrets_string() {
    char* secrets = (char*)malloc(sizeof(char) * BUFF_SIZE); 
    int secrets_size = strlen(secrets) ; 
    char* fuzzer_string[3]; 

    for(int i = 0 ; i < 3 ; i++) { 
        fuzzer_string[i] = fuzzer(BASIC_LENGTH, BASIC_START, BASIC_RANGE); 
    }
    sprintf(secrets, "<space-for-reply>%s<secret-certificate>%s<secret-key>%s<other-secrets>", 
        fuzzer_string[0], fuzzer_string[1], fuzzer_string[2]);

    char uninitialized_memory_marker[9] = "deadbeef";
    int uninit_memorymaker_size = strlen(uninitialized_memory_marker) ; 
 
    while( secrets_size + uninit_memorymaker_size + 1 < BUFF_SIZE) {
        strcat(secrets, uninitialized_memory_marker); 
        secrets_size += uninit_memorymaker_size ;
    }
    
    for(int i = 0 ; i < 3; i++) { 
        free(fuzzer_string[i]);
    }
    return secrets; 
} 

char* heartbeat(char* reply, int length, char* memory) {
    char * substr = substring(memory, strlen(reply), strlen(memory));
    sprintf(memory, "%s%s", reply, substr);

    char* s = (char*)malloc(sizeof(char) * (length + 1));
    for(int i = 0 ; i < length ; i++) {
        s[i] = memory[i];
    }
    s[length] = '\0';
    free(substr); 
    return s ;
}

void information_leaks_test1() {
    char* secrets = make_secrets_string(); 

    printf("[Information Leaks Test1]\n");
    printf("%s\n", heartbeat("potato", 6, secrets)); 
    printf("%s\n", heartbeat("bird", 4, secrets));
    printf("%s\n\n", heartbeat("hat", 500, secrets)); 
}

void information_leaks_test2() {
    printf("[Information Leaks Test2]\n");
    char* secrets = make_secrets_string(); 
    char uninitialized_memory_marker[9] = "deadbeef";

    for(int i = 0 ; i < 10; i++) {
        char* s = heartbeat(fuzzer(BASIC_LENGTH, BASIC_START, BASIC_RANGE), 1 + rand()%500, secrets);
        assert(strstr(s, uninitialized_memory_marker) == NULL);
        assert(strstr(s, "secret") == NULL);
        free(s);
    }
    free(secrets);
}

int main(void) {
    srand(time(0)); 
    information_leaks_test1(); 
    information_leaks_test2();
    return 0;
}

