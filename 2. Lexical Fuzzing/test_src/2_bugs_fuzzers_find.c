#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
#include "../include/simpleFuzzer.h"

void crash_if_too_long(char * random_string_by_fuzzer) {
    char buffer[] = "Thursday"; 
    if( strlen(random_string_by_fuzzer) > strlen(buffer) ) {
        printf("ValueError!\n");
        exit(1);
    }
}

void buffer_overflows() {
    int trials = 100; 
    for(int i = 0 ; i < trials; i++) {
        char * basic_random = fuzzer(BASIC_LENGTH, BASIC_START, BASIC_RANGE); 
        crash_if_too_long(basic_random);
    }
}

void handler(int sig)
{
    printf("Time out! (2 seconds)\n");
    exit(0); 
}

void hang_if_no_space(char * random_string_by_fuzzer) {
    int i = 0 ;

    while(1) {
        if (i < strlen(random_string_by_fuzzer)) {
            if(random_string_by_fuzzer[i] == ' ') {
                break;
            }
        }
        i++; 
    }
}

void missing_error_checks() { 
    int trials = 100; 
    
    struct itimerval t; 
    
    signal(SIGALRM, handler); 

    t.it_value.tv_sec = 2; 
    t.it_interval = t.it_value ;

    setitimer(ITIMER_REAL, &t, 0x0); 

    for(int i = 0 ; i < trials; i++) {
        char * basic_random = fuzzer(BASIC_LENGTH, BASIC_START, BASIC_RANGE); 
        hang_if_no_space(basic_random);
        free(basic_random);
    }
}

void collapse_if_too_large(char * random_string_by_fuzzer) {
    if(atoi(random_string_by_fuzzer) > 1000 || atoi(random_string_by_fuzzer) < 0) {
        printf("ValueError!\n");
        exit(1);
    }
}

void rogue_number() {
    char *long_number = fuzzer(BASIC_LENGTH, (int)'0', 10) ;
    collapse_if_too_large(long_number);
    printf("%s\n", long_number);
    free(long_number);
}   

int main(void) {
    buffer_overflows(); 
    missing_error_checks(); 
    rogue_number(); 

    return 0; 
}