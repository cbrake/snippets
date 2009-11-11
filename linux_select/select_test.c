/* test code to test select */


#include <stdio.h>
#include <sys/select.h>

main()
{
	/* the below will block forever */
	select(0, NULL, NULL, NULL, NULL);
	printf("Should never get here because select should block forever\n");
}

