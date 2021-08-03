#include <stdio.h>
#include <math.h>
#include <stdlib.h> 
#include <assert.h>

double my_sqrt(double x) {
    double value = 0; 
    double guess = x / 2; 
    while(value != guess) {
        value = guess; 
        guess = ( value + x / value )/ 2; 
    }
    return value; 
}

double my_sqrt_fixed(int x) {
    assert(0 <= x); 
    if(x == 0) {
        return 0 ; 
    }
    return my_sqrt(x) ;
}

double* quadratic_solver(double a, double b, double c) {
    double *sol = (double*)malloc(sizeof(double) * 2); 
    int q = b * b - 4 * a * c ; // b^2 - 4ac
    sol[0] = (-b + my_sqrt_fixed(q)) / (2*a); 
    sol[1] = (-b - my_sqrt_fixed(q)) / (2*a); 
    return sol; 
}

double* quadratic_solver_fixed(double a, double b, double c) {
    // ax^2 + bx + c = 0 
    double * sol ; 
    if (a == 0) {
        if (b == 0) {
            if (c == 0) {
                sol = (double*)malloc(sizeof(double)) ; 
                sol[0] = 0 ; 
                return sol; 
            }else{
                return NULL; 
            }   
        }else{
            sol = (double*)malloc(sizeof(double)) ; 
            sol[0] = - c / b ; 
            return sol; 
        }
    }

    double q = b * b - 4 * a * c ; // b^2 - 4ac
    if( q < 0 ) return NULL; 
    if( q == 0 ) {
        sol = (double*)malloc(sizeof(double)) ; 
        sol[0] = -b / 2 * a; 
        return sol; 
    }
    sol = (double*)malloc(sizeof(double) * 2); 
    sol[0] = (-b + my_sqrt_fixed(q)) / (2*a); 
    sol[1] = (-b - my_sqrt_fixed(q)) / (2*a); 
    return sol; 
} 

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