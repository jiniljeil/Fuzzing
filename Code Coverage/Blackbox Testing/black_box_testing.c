#include "include/coverage.h" 
#include <assert.h>
#include <stdio.h> 
#include <string.h> 
// #define VALUE_ERROR 
void test_1() {
    char text1[10], text2[10], text3[10];  

    printf("---------------------TEST1---------------------\n"); 
    cgi_decode(text1, "+"); 
    assert(strcmp(text1, " ") == 0); 
    cgi_decode(text2, "%20"); 
    assert(strcmp(text2, " ") == 0); 
    cgi_decode(text3, "abc");
    assert(strcmp(text3, "abc") == 0); 

    printf("cgi_decode(\"+\") == \"%s\"\n", text1 ) ; 
    printf("cgi_decode(\"%%20\") == \"%s\"\n", text2) ; 
    printf("cgi_decode(\"abc\") == \"%s\"\n", text3) ; 
#ifdef VALUE_ERROR 
    cgi_decode("%?a") ; 
#endif
    printf("-----------------------------------------------\n"); 
}

void test_2() {
    char text1[20], text2[10]; 
    printf("---------------------TEST2---------------------\n"); 
    cgi_decode(text1, "Hello+world");
    printf("cgi_decode(\"Hello+world\") == \"%s\"\n", text1); 

    cgi_decode(text2, "a+b");
    printf("cgi_decode(\"a+b\") == \"%s\"\n", text2); 
    printf("-----------------------------------------------\n"); 
}

int main(void) {
    test_1(); 
    test_2(); 
}