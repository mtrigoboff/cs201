// starter file for Assignment 3

#include <stdio.h>
#include <stdlib.h>

#define PRECISION   3

double sumD(double x, double y)
{
    double      sum = 0.0;

// do not change anything above this comment

    return sum;

// do not change anything below this comment, except for printing out your name
}

int main(int argc, char **argv)
{
    double  x = 0.0;
    double  y = 0.0;

    printf("CS201 - Assignment 02 - I. Forgot\n");
    if (argc == 3) {
        x = atof(argv[1]);
        y = atof(argv[2]);
        }

    printf("%.*f  + %.*f = %.*f\n", PRECISION, x, PRECISION, y, PRECISION, sumD(x, y));

    return 0;
}
