// put Fibonacci terms into esi

int main (int argc, char **argv)
{
	int		f1 = 2;
	int		f2 = 3;
	int		new;
	int		i;
	
	asm("		mov		$0xABCD, %esi");
	for (i = 0; i < 3; i++) {
		new = f2 + f1;
		f1 = f2;
		f2 = new;
		asm("		mov		%0, %%esi"		: : "m" (f2));
		}
	
	return 0;
}
