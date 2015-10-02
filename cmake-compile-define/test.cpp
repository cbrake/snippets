#include <stdio.h>

main() 
{
#if TESTDEFINE
	printf("TESTDEFINE defined\n");
#else
	printf("TESTDEFINE not defined\n");
#endif
}

