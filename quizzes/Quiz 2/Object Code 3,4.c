// not 100% sure this is the source code for this question

#include <stdio.h>
#include <stdlib.h>

int what (int m, int n)
{
	int		x = m + 4;
	int		y = m * n;
	int		z = m - n;

	return x + y + z;
}

int main (int argc, char **argv)
{
	int		a1 = atoi(argv[1]);
	int		a2 = atoi(argv[2]);
	int		val;

	val = what(a1 + 2, a2 + 1);
	printf("val = %d\n", val);

	return 0;
}
