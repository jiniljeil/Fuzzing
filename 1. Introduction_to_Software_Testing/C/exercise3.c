#include <stdio.h>
#include <math.h>
#include <stdlib.h> 
#include <assert.h>
#include "lib/quadratic.h"

void part1_find_bug_triggering_inputs() {
    double *q_solver; 
    
    q_solver = quadratic_solver(0, 1, 2); // division zero error 
    printf("(%.6lf, %.6lf)\n", q_solver[0], q_solver[1]); 
    free(q_solver); 

    q_solver = quadratic_solver(2, 1, 2); // assert occurs
    printf("(%.6lf, %.6lf)\n", q_solver[0], q_solver[1]); 
    free(q_solver);
}   

void part2_fix_the_problem() {
    double *q_solver ;  

    q_solver = quadratic_solver_fixed(1, 2, 3); // b^2 - 4ac < 0
    if (q_solver == NULL) printf("1. 해가 존재하지 않습니다.\n");
    else printf("1. (%.6lf, %.6lf)\n", q_solver[0], q_solver[1]); 

    q_solver = quadratic_solver_fixed(1, -4, 3); // b^2 - 4ac > 0
    if (q_solver == NULL) printf("2. 해가 존재하지 않습니다.\n");
    else printf("2. (%.6lf, %.6lf)\n", q_solver[0], q_solver[1]); 

    q_solver = quadratic_solver_fixed(1, 2, 1);  // b^2 - 4ac = 0 
    if (q_solver == NULL) printf("3. 해가 존재하지 않습니다.\n");
    else printf("3. (%.6lf, %.6lf)\n", q_solver[0], q_solver[1]); 
}

void part3_odds_and_ends() {
    unsigned long long combination = 1; 
    combination = (combination << 63); 
    
    unsigned long long year = (60 * 60 * 24 * 365) ;
    unsigned long long second = 1e9; 

    printf("\nIf we can do a billion tests per second, how many years would we have to wait?\n"); 
    printf("Year: %llu\n", (combination / (second * year)) * 2 );
}

int main(void){
    // Error 
    // a = 0 (a division by zero)
    // q < 0 (q is a negative value)
    
    // q_solver = quadratic_solver(3, 4, 1); // (a, b, c)  
    // q_solver = quadratic_solver(0, 0, 1); 

    printf("\nExercise 3: Quadratic Solver\n");
    part1_find_bug_triggering_inputs(); 
    part2_fix_the_problem();
    part3_odds_and_ends(); 

    return 0;
}