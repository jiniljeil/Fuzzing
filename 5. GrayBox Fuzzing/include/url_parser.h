
#define true 1 
#define false 0 

typedef struct url {
    char * scheme; // the protocol to be used, including http, https, ftp, file...
    char * netloc; // the name of the host to connect to, such as www.google.com
    char * path ;  // the path on that very host, such as search 
    char * port ; 
    char * query ; // a list of key/value pairs, such as q=fuzzing
    char * fragment ; // a marker for a location in the retrieved document, such as #result
} url_t; 

int url_parser(char * url, url_t * url_info); 
int http_program(char * url); 
int is_valid_url(char * url); 
