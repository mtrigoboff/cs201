// sequence of values in esi

int		values[] = {0xABCD, 0xDEAD, 0xDEAF, 0xBEEF};

int main (int argc, char **argv)
{
	int		*p = values;
	
	asm("		mov		%[p], %%esi				\n"
		"		mov		(%%esi), %%edi			\n"
		"		add		$12, %%esi				\n"
		"		mov		(%%esi), %%edi			\n"
		"		sub		$8, %%esi				\n"
		"		mov		(%%esi), %%edi			\n"
		"		add		$4, %%esi				\n"
		"		mov		(%%esi), %%edi			\n"
		: 											// outputs
		: [p]			"m"			(p));			// inputs
	
	return 0;
}

/* older version, maybe better in producing more complex-looking assembly code

// sequence of values in esi

int		values[] = {0xABCD, 0xDEAD, 0xDEAF, 0xBEEF};

int main (int argc, char **argv)
{
	int		i;
	
	for (i = 0; i < 4; i++)
		asm("	mov		%0, %%esi"			: : "m" (values[i]));
	
	return 0;
}
*/
