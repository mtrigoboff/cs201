int main (int argc, char **argv)
{
	asm("	mov		$0xABCD, %esi");
	asm("	mov		$0x1234, %esi");
	asm("	inc		%esi");
	asm("	add		$2, %esi");
	
	return 0;
}
