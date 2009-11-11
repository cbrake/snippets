/* simple linux timer test */


#include <stdio.h>
#include <sys/time.h>
#include <sys/select.h>
#include <signal.h>
#include <string.h>

/* notes, the below timer generates a SIGALRM.
 * If this signal is not handled, the program 
 * exits
 */

void timer_handler(int sig)
{
	printf("timer_handler\n");
}

main ()
{
	/* set up handler for SIGALRM */
	struct sigaction sa;

	memset(&sa, 0, sizeof(sa));

	sa.sa_handler = &timer_handler;
	sigaction(SIGALRM, &sa, NULL);

	/* set up timer */
	struct itimerval itv;

	itv.it_value.tv_sec = 1;
	itv.it_value.tv_usec = 0;
	itv.it_interval.tv_sec = 1;
	itv.it_interval.tv_usec = 0;
	setitimer(ITIMER_REAL, &itv, NULL);

	/* block forever */
	while (1) {
		select(0, NULL, NULL, NULL, NULL);
		printf("main loop became unblocked\n");
	}
}

