#include "include/coverage.h" 
#include <assert.h>
#include <stdio.h> 
#include <string.h> 
// #define VALUE_ERROR 
void test_1() {
    printf("---------------------TEST1---------------------\n"); 
    assert(strcmp(cgi_decode("+"), " ") == 0); 
    assert(strcmp(cgi_decode("%20"), " ") == 0); 
    assert(strcmp(cgi_decode("abc"), "abc") == 0); 

    printf("cgi_decode(\"+\") == \"%s\"\n", cgi_decode("+")) ; 
    printf("cgi_decode(\"%%20\") == \"%s\"\n", cgi_decode("%20")) ; 
    printf("cgi_decode(\"abc\") == \"%s\"\n", cgi_decode("abc")) ; 
#ifdef VALUE_ERROR 
    cgi_decode("%%?a") ; 
#endif
    printf("-----------------------------------------------\n"); 
}

void test_2() {
    printf("---------------------TEST2---------------------\n"); 
    printf("cgi_decode(\"Hello+world\") == \"%s\"\n", cgi_decode("Hello+world")); 
    printf("cgi_decode(\"a+b\") == \"%s\"\n", cgi_decode("a+b")); 
    printf("-----------------------------------------------\n"); 
}
int main(void) {
    test_1(); 
    test_2(); 
}