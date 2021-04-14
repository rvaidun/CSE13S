#include "mathlib.h"

#include <math.h>

#define EPSILON 1E-10
#define M_PI    3.14159265358979323846264338327950288

double abs(double x) {
    return (x > 0) ? x : -x;
}
// Solve arcsin with newtons method
double arcSin(double x) {
    double oldguess;
    double guess = 1;
    double answer = sin(guess) - x;
    while (abs(answer) > EPSILON) {
        oldguess = guess;
        guess = oldguess - (sin(guess) - x / cos(guess));
        answer = sin(guess - x);
    }
    return answer;
}
