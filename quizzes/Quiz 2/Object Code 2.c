#include <stdlib.h>

int main (int argc, char **argv)
{
	int		n = 0;
	int		i;

	for (i = 1; i < argc; i++)
		n += atoi(argv[i]);

	return n;
}
