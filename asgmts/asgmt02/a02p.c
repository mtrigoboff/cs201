// starter file for Assignment 02p

#include <stdio.h>
#include <stdlib.h>

#define PRECISION           3
#define RND_CTL_BIT_SHIFT   10

// floating point rounding modes: IA-32 Manual, Vol. 1, p. 4-20
typedef enum {
    ROUND_NEAREST_EVEN =    0 << RND_CTL_BIT_SHIFT,
    ROUND_MINUS_INF =       1 << RND_CTL_BIT_SHIFT,
    ROUND_PLUS_INF =        2 << RND_CTL_BIT_SHIFT,
    ROUND_TOWARD_ZERO =     3 << RND_CTL_BIT_SHIFT
} RoundingMode;

double roundD(double n, RoundingMode roundingMode)
{
// do not change anything above this comment

    return n;

// do not change anything below this comment, except for printing out your name
}

int main(int argc, char **argv)
{
    double  n = 0.0;

    printf("CS201 - Assignment 02p - your name\n");
    if (argc > 1)
        n = atof(argv[1]);

    printf("roundD even %.*f = %.*f\n",
           PRECISION, n, PRECISION, roundD(n, ROUND_NEAREST_EVEN));
    printf("roundD down %.*f = %.*f\n",
           PRECISION, n, PRECISION, roundD(n, ROUND_MINUS_INF));
    printf("roundD up   %.*f = %.*f\n",
           PRECISION, n, PRECISION, roundD(n, ROUND_PLUS_INF));
    printf("roundD zero %.*f = %.*f\n",
           PRECISION, n, PRECISION, roundD(n, ROUND_TOWARD_ZERO));

    return 0;
}
