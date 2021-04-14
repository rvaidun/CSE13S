#include <assert.h>
#include <math.h>
#include <stdio.h>
#define EPSILON 1E-10
#define PI      3.14159265358979323846264338327950288

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
double arcSin(double a) {
    double answer = a;
    do {
        answer = answer - ((sin(answer) - a) / cos(answer));
    } while (Abs(sin(answer) - a) > EPSILON);
    return answer;
}

// Solves arccos using implementation of arcSin
double arcCos(double x) {
    return (PI / 2) - arcSin(x);
}

// Solves arctan using implementation of arcSin
double arcTan(double x) {
    return arcSin(x / (sqrt(x * x) + 1));
}

double Log(double a) {
    double answer = a;
    do {
        answer = answer - ((Exp(answer) - a) / Exp(answer));
    } while (Abs(Exp(answer) - a) > EPSILON);
    return answer;
}
