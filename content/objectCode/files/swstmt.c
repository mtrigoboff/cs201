// compilation of switch statement

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
    int     x = argc > 1 ? atoi(argv[1]) : 0;
    int     y;
    
    switch (x) {
        case 0:
            y = 0;
            break;
        case 1:
            y = 1;
            break;
        case 2:
            y = 2;
            break;
        case 3:
            y = 3;
            // this case "drops through"
        case 4:
            y = 4;
            break;
        default:
            y = -1;
            break;
        }
    
    printf("x = %d, y = %d\n", x, y);
    return 0;
}
