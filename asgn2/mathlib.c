#include <assert.h>
#include <math.h>
#include <stdio.h>
#define EPSILON 1E-10
#include "mathlib.h"
// Returns absolute value of a double
double Abs(double x) {
    return (x > 0) ? x : -x;
}

// Returns the Square root of a function
// Code from Piazza posted by Professor Darrell Long
double Sqrt(double x) {
    double y = 1.0;
    assert(x >= 0);
    for (double guess = 0.0; Abs(y - guess) > EPSILON; y = (y + x / y) / 2.0) {
        guess = y;
    }
    return y;
}

// Returns e^x
// Code from Piazza posted by Professor Darell Long
double Exp(double x) {
    double term = 1, sum = 1;
    for (int k = 1; Abs(term) > EPSILON; k += 1) {
        term *= x / k;
        sum += term;
    }
    return sum;
}

// Solve arcsin of x with newtons method
// Refer to Design PDF for formula
double arcSin(double x) {
    // As x gets closer to 1 accuracy is rapidly lost
    // To fix this issue we can use trig identities and calculate arcsin in terms of arccos
    // Refer to Design PDF and WRITEUP PDF for more details
    if (Abs(x) > 0.9) {
        // When x is negative we have to return - arcCos
        return (x > 0.9) ? arcCos(Sqrt(1 - (x * x))) : -arcCos(Sqrt(1 - (x * x)));
    }

    double answer = x; // Initial guess is x
    while (Abs(sin(answer) - x) > EPSILON) { // Stop when the difference is smaller then epsilon
        answer = answer - ((sin(answer) - x) / cos(answer)); // New answer
    }
    return answer;
}

// Solves arccos using implementation of arcSin
// Refer to deign PDF for formula
double arcCos(double x) {
    return (M_PI / 2) - arcSin(x);
}

// Solves arctan using implementation of arcSin
// Refer to Design PDF for formula
double arcTan(double x) {
    return arcSin(x / (sqrt((x * x) + 1)));
}

// Solve Log using Newtons Method
// Refer to Design PDF for formula
double Log(double a) {
    double answer = a;
    while (Abs(Exp(answer) - a) > EPSILON) {
        answer = answer - ((Exp(answer) - a) / Exp(answer));
    }
    return answer;
}
