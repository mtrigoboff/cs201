#include <stdlib.h>

int main (int argc, char **argv)
{
	register int		n		asm("edx")		= 0;

	n += argc;

	return n;
}
