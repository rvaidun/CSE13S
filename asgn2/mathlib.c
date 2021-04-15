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
// Refer to Design PDF for formula
double arcSin(double x) {
    double a;
    // As x gets closer to 1 accuracy is rapidly lost
    // To fix this issue we can use trig identities and calculat arcsin in terms of arccos
    // Refer to Design PDF for more details
    if (Abs(x) > 0.9) {
        a = Sqrt(1 - (x * x));
    } else {
        a = x;
    }

    double answer = a;
    while (Abs(sin(answer) - a) > EPSILON) { // Stop when the difference is smaller then epsilon
        answer = answer - ((sin(answer) - a) / cos(answer)); // New answer
    }
    if (Abs(x) > 0.9) {
        // Because we are using arccos method subtract from pi/2
        return (x < 0) ? -((PI / 2) - answer) : (PI / 2) - answer;
    } else {
        return answer;
    }
}

// Solves arccos using implementation of arcSin
// Refer to deign PDF for formula
double arcCos(double x) {
    return (PI / 2) - arcSin(x);
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
