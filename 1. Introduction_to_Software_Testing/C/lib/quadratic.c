#include "quadratic.h"
#include "my_sqrt.h"
#include <stdlib.h>

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