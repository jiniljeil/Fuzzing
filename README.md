## The Fuzzing 
> Fuzzing is a dynamic testing method among software testing methods that test a program by giving random input values to the target program.

## Fuzzer Architecture 
<img src="./images/Fuzzer Architecture.png" alt="Fuzzer\ Architecture">

### Workflow (Boosted GrayBox Fuzzing)
1. Configuration by user 
    - target program path 
    - trial, test oracle, mutation
2. Fuzzer run & Configuration Setting check 
3. Load seed data & Mutation (mutation opertaors)
    - delete_random_character 
    - insert_random_character
    - bit_flip_random_character
    - byte_flip_random_character
    - byte_simple_arithmatic
    - known_integer
4. Normalize seed choice proportion & Choose the seed probabilistically
4. Execute target program & gcov
5. Get the execution result as pipe and conduct a test oracle & Read the gcov file to get coverage information
6. Repitition 3~5 steps
7. Summary

### Link 
> ### <a href="https://www.fuzzingbook.org/html/Tours.html">Tours through the Book</a>

### Step
1. Introduction to Software Testing
2. Fuzzing: Breaking Things with Random Inputs 
3. Code coverage 
4. Mutation-Based Fuzzing 
5. Graybox Fuzzing
6. Boosted Graybox Fuzzing
