// demonstrates jumping up the stack

#include <stdio.h>

static int		nLevels = 3;

void down(int n)
{
	printf("down(%d) called\n", n);
	if (n == 1) {
		printf("down(%d) jumping up the stack to main()\n", n);
		asm(
			"		movl	%[nLevels], %%eax		\n"
			"	up:	movl	(%%ebp), %%ebp			\n"
			"		dec		%%eax					\n"
			"		cmp		$1, %%eax				\n"
			"		jne		up						\n"
			"		movl	%%ebp, %%esp			\n"
			"		pop		%%ebp					\n"
			"		ret								\n"
		:											// no outputs
		:	[nLevels]	"m"		(nLevels)			// input
		: "eax"										// clobber
		);
		}
	else {
		down(n - 1);
		printf("down(%d) returning\n", n);
		}
}

int main(int argc, char **argv)
{
	printf("main() about to call down(%d)\n", nLevels);
	down(nLevels);
	printf("down(%d) returned to main()\n", nLevels);

	return 0;
}
