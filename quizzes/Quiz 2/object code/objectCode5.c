// question 5

#include <stdio.h>
#include <stdlib.h>

// factorial
int what (int n)
{
    int     f;
    
    if (n <= 1)
        f = 1;
    else
        f = n * what(n - 1);
        
    return f;
}

int main (int argc, char **argv)
{
    register int    arg     asm("ebx");
    int             val;
    
    if (argc != 2) {
        printf("one numeric argument required\n");
        return -1;
        }

    arg = atoi(argv[1]);
    val = what(arg);
    
    return 0;
}
