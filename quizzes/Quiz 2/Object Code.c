int main (int argc, char **argv)
{
	int		array[2][3];
	
	// quiz 5: this code steps through the array using an "outer" and an "inner" counter
	// (this code is quite compiler-dependent -
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
		"			movl	$0x2b,0xffffffdc(%%ebp)				\n"		// initialize array (start)
		"			movl	$0x31,0xffffffe4(%%ebp)				\n"
		"			movl	$0x74,0xffffffec(%%ebp)				\n"
		"			movl	$0x19,0xffffffe8(%%ebp)				\n"
		"			movl	$0x7,0xffffffd8(%%ebp)				\n"
		"			movl	$0x14,0xffffffe0(%%ebp)				\n"		// initialize array (end)
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
