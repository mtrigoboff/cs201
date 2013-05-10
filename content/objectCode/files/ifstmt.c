// compilation of an if statement

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
    int     x = argc > 1 ? atoi(argv[1]) : 0;
    char    *str;
    
    if (x <= 0)
        str = "zero";
    else if (x == 1)
        str = "one";
    else if (x == 2)
        str = "two";
    else
        str = "> two";

    printf("x = %d, str = \"%s\"\n", x, str);
    return 0;
}
