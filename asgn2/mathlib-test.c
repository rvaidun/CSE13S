#include "mathlib.h"

#include <math.h>
#include <stdio.h>
#include <unistd.h> // For getopt().
#define OPTIONS "asctl"

int main(int argc, char **argv) {
    // Command Line argument code influnecned by Lab Document
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 's':
            printf("  x            arcSin           Library        Difference\n");
            printf("  -            ------           -------        ----------\n");
            for (double x = -1; x < 1; x += 0.1) {
                double implemented = arcSin(x);
                double library = asin(x);
                printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", x, implemented, library,
                    implemented - library);
            }
            break;
        case 'c':
            printf("  x            arcCos           Library        Difference\n");
            printf("  -            ------           -------        ----------\n");
            for (double x = -1; x < 1; x += 0.1) {
                double implemented = arcCos(x);
                double library = acos(x);
                printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", x, implemented, library,
                    implemented - library);
            }
            break;
        case 't':
            printf("  x            arcTan           Library        Difference\n");
            printf("  -            ------           -------        ----------\n");
            for (double x = 1; x < 10; x += 0.1) {
                double implemented = arcTan(x);
                double library = atan(x);
                printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", x, implemented, library,
                    implemented - library);
            }
            break;
        case 'l':
            printf("  x            Log           Library        Difference\n");
            printf("  -            ------           -------        ----------\n");
            for (double x = 1; x < 10; x += 0.1) {
                double implemented = Log(x);
                double library = log(x);
                printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", x, implemented, library,
                    implemented - library);
            }
        }
    }
}
