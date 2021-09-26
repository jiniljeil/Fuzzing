#ifndef MUTATION 
#include <stdlib.h>
#include "schedule.h"
#define INTERESTING_8 \
  -128,          /* Overflow signed 8-bit when decremented  */ \
  -1,            /*                                         */ \
   0,            /*                                         */ \
   1,            /*                                         */ \
   16,           /* One-off with common buffer size         */ \
   32,           /* One-off with common buffer size         */ \
   64,           /* One-off with common buffer size         */ \
   100,          /* One-off with common buffer size         */ \
   127           /* Overflow signed 8-bit when incremented  */

#define INTERESTING_16 \
  -32768,        /* Overflow signed 16-bit when decremented */ \
  -129,          /* Overflow signed 8-bit                   */ \
   128,          /* Overflow signed 8-bit                   */ \
   255,          /* Overflow unsig 8-bit when incremented   */ \
   256,          /* Overflow unsig 8-bit                    */ \
   512,          /* One-off with common buffer size         */ \
   1000,         /* One-off with common buffer size         */ \
   1024,         /* One-off with common buffer size         */ \
   4096,         /* One-off with common buffer size         */ \
   32767         /* Overflow signed 16-bit when incremented */

#define INTERESTING_32 \
  -2147483648LL, /* Overflow signed 32-bit when decremented */ \
  -100663046,    /* Large negative number (endian-agnostic) */ \
  -32769,        /* Overflow signed 16-bit                  */ \
   32768,        /* Overflow signed 16-bit                  */ \
   65535,        /* Overflow unsig 16-bit when incremented  */ \
   65536,        /* Overflow unsig 16 bit                   */ \
   100663045,    /* Large positive number (endian-agnostic) */ \
   2147483647    /* Overflow signed 32-bit when incremented */

static u_int8_t  interesting_8[]  = { INTERESTING_8 };
static u_int16_t interesting_16[] = { INTERESTING_8, INTERESTING_16 };
static u_int32_t interesting_32[] = { INTERESTING_8, INTERESTING_16, INTERESTING_32 };

int store_seed_files(char * seed_dir, char * storage[]);
int add_seed_file(char * seed_dir, char * new_seed_input[], int * num_of_seed_files, char * input, int input_len) ; 
int delete_random_character(char * deleted_string, char * seed_input, int seed_length) ; 
int insert_random_character(char * inserted_string, char * seed_input, int seed_length) ; 
int bit_flip_random_character(char * flip_string,char * seed_input, int seed_length) ; 
int byte_flip_random_character(char * byte_flip_string, char * seed_input, int seed_length) ;
int byte_simple_arithmatic(char * arith_string, char * seed_input, int seed_length); 
int known_integer(char * integer_string, char * seed_input, int seed_length); 
int load_seed_inputs(seed_t * seed_set, char * seed_file_storage[] , int num_of_seeds); 
int mutate(char * string, char * seed_input, int seed_length) ;
int mutate_input(char * input, seed_t * seed_set, energy_set_t * energy_set, int mutation) ; 
#endif