#include "mathlib.h"

// Rahul Vaidun
// April 2021
#include <math.h>
#include <stdio.h>
#include <unistd.h> // For getopt().
#define OPTIONS "asctl"

// Shows Differences for function that is passed to it
// pass name that should be printed as header
// Pass when test should start and when test should stop
// Pass pointer to implementation and pointer to the library function
void showDifference(
    char *name, double start, double stop, double (*i)(double), double (*l)(double)) {
    printf("  %-12s %-16s %-14s %s \n", "x", name, "Library", "Difference");
    printf("  %-12s %-16s %-14s %s \n", "-", "------", "-------", "----------");
    for (double x = start; x < stop; x += 0.1) {
        double implemented = (*i)(x);
        double library = (*l)(x);
        printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", x, implemented, library,
            implemented - library);
    }
}
int main(int argc, char **argv) {
    // Command Line argument code influenced by Lab Document

    if (argc == 1) { // If there is only one argument print program usage and return
        printf("Program usage: ./mathlib-test -[asctl]\n-a   Runs all tests (arcsin, arccos, "
               "arctan, log)\n-s   Runs arcsin tests\n-c   Runs arccos tests\n-t   Runs arctan "
               "tests\n-l   Runs log tests\n");
        return -1;
    }

    int opt = 0;
    // First while loop is to make sure all arguemnts are valid.
    // If arguemnt is invalid print error and exit
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        if (opt == '?') {
            printf("Program usage: ./mathlib-test -[asctl]\n-a   Runs all tests (arcsin, arccos, "
                   "arctan, log)\n-s   Runs arcsin tests\n-c   Runs arccos tests\n-t   Runs arctan "
                   "tests\n-l   Runs log tests\n");
            return -1;
        }
    }

    optind = 1; // reset index of getopt to 1 so we can use it again on argv
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 's': // arcSin
            showDifference("arcSin", -1, 1, arcSin, asin);
            break;
        case 'c': // arcCos
            showDifference("arcCos", -1, 1, arcCos, acos);
            break;
        case 't': //arcTan
            showDifference("arcTan", 1, 10, arcTan, atan);
            break;
        case 'l': // Log
            showDifference("Log", 1, 10, Log, log);
            break;
        default: // All
            showDifference("arcSin", -1, 1, arcSin, asin);
            showDifference("arcCos", -1, 1, arcCos, acos);
            showDifference("arcTan", 1, 10, arcTan, atan);
            showDifference("Log", 1, 10, Log, log);
        }
    }
    return 0;
}
