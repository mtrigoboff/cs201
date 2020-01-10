// question is not based on this code, but it was there in the directory
// so I copied it over in case it might prove to be useful someday

int main (int argc, char **argv)
{
	int		array[2][3];

	// quiz 5: this code steps through the array using an "outer" and an "inner" counter
	// (currently the quiz is based on quiz05a.c, but that one is quite compiler-dependent -
	//  it has the offset of the beginning of the array from ebp hard-coded)
	//
	// registers:
	//		eax			address of array, address of array element
	//		ebx			outer index, row offset, array element offset
	//		ecx			loop counters
	//		edx			inner index
	//		esi			save outer counter
	//		edi			target for data

	asm(
		"			lea		%[array],%%eax						\n"		// address of array
		"			movl	$0x2b,4(%%eax)						\n"		// initialize array (start)
		"			movl	$0x31,12(%%eax)						\n"
		"			movl	$0x74,20(%%eax)						\n"
		"			movl	$0x19,16(%%eax)						\n"
		"			movl	$0x7,(%%eax)						\n"
		"			movl	$0x14,8(%%eax)						\n"		// initialize array (end)
		"			mov		$0xDEAD, %%edi						\n"
		"			mov		$2, %%ecx							\n"		// initialize outer counter
		"outer:		mov		%%ecx, %%esi						\n"		// save outer counter
		"			mov		$3, %%ecx							\n"		// initialize inner counter
		"inner:		mov		$2, %%ebx							\n"		// initialize outer index
		"			sub		%%esi, %%ebx						\n"		// subtract outer counter
		"			imul	$12, %%ebx							\n"		// compute row offset
		"			mov		$3, %%edx							\n"		// initialize inner index
		"			sub		%%ecx, %%edx						\n"		// subtract inner counter
		"			lea		%[array], %%eax						\n"		// address of array
		"			lea		(%%ebx,%%edx,4), %%ebx				\n"		// offset of element
		"			add		%%ebx, %%eax						\n"
		"			mov		(%%eax), %%edi						\n"		// element data
		"			loop	inner								\n"
		"			mov		%%esi, %%ecx						\n"		// restore outer counter
		"			loop	outer								\n"
		"			mov		$0xBEEF, %%edi						\n"
		:																// outputs
		: [array] "m" (array[0][0])										// inputs
	);

	return 0;
}
