int main (int argc, char **argv)
{
	int		x;

	{
	register int	sum		asm("edx")		= 0;
	register int	i		asm("ecx");

	for (i = 0; i < 10; i++)
		sum += i;
	x = sum;
	}

	return 0;
}
