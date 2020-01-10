int main (int argc, char **argv)
{
	int		x;

	{
	register int	val		asm("edx")		= 1;
	register int	n		asm("ecx")		= 8;

	for ( ; n > 0; n--)
		val += n + n - 1;
	x = val;
	}

	return 0;
}
