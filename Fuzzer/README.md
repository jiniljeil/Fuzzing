## Random Fuzzer 

RandomFuzzer consists of the type of three. It makes the random input and runs the program based on input.

### [Fuzzer Configuration]
1. Create inputs
2. Run the program  
3. Test oracle 

## Setting  

User can set the configuration through config declared on the <strong>"include/config.h"</strong>. For example, if the user wants to test the program, it can proceed in the following way. 

1. Declare the variable type of <strong>test_config_t</strong>. 
2. Call the <strong>config_init</strong> function.   
3. Enter the program name on the <strong>config.binary_path</strong>.  
4. Additional working (optional)
    - send arguments(options) of the program 
    - set the length of random string 
    - set the timeout 
    - set the customized test oracle 


### Default test oracle 
This judges the result from the return code of test program. 

### Current Test Driver  
1. **/bin/cat** program 
2. **troff** program 
