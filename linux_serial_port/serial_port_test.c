/* test serial port */


/* test blocking reads with timeout */

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <sys/select.h>

main()
{
	struct termios newtio;
	int fd;

	fd = open("/dev/ttyS0", O_RDWR);

	if (fd < 0) {
		printf("Error opening serial port\n");
		exit(-1);
	}

	memset(&newtio, 0, sizeof(newtio));

	/* man termios get more info on below settings */
	/* CS8 - character size mask
	 * CLOCAL - ignore modem control lines
	 * CREAD - enable receiver
	 */
	newtio.c_cflag = B115200 | CS8 | CLOCAL | CREAD;	/* control modes */
	newtio.c_iflag = 0;	/* input mode */
	newtio.c_oflag = 0;	/* output modes */
	newtio.c_lflag = 0;	/* local modes */

/*
VMIN specifies the minimum number of bytes to read before read() returns. 
VTIME is the time to wait (in tenths of a second) before returning from 
read (). VMIN and VTIME are used only when the ICANON flag is clear in 
the c_lflag parameter. In the previous example, you probably noticed 
that c_cc[VMIN] and c_cc[VTIME] were set to 1 to enable non-blocking 
reads. Many programmers are confused by VMIN and VTIME, but the rules are 
reasonably simple; four possible combinations of VMIN and VTIME are 
possible, as follows (from POSIX.1, 7.1.1.7):

VMIN > 0 and VTIME > 0
    TIME is an interbyte timer that is activated after the first byte
    is received and is reset after each received byte. If the timer 
    expires, at least one byte has been received because the timer 
    is not activated until after a byte has been received. 
VMIN > 0 and VTIME = 0
    There is no timer, so read() returns when MIN bytes have been 
    received or when a signal is received. 
VMIN = 0 and VTIME > 0
    Because MIN is 0, TIME is a read () operation timer that is 
    activated as soon as read() is called. The read() operation 
    returns as soon as a byte is received or when the timer expires. 
VMIN = 0 and VTIME = 0
    The read() operation returns immediately with the data that is 
    in the input buffer. If the input buffer is empty, read() 
    returns immediately with zero bytes of data. 
*/
	tcflush(fd, TCIFLUSH);

	int count;
	char buffer[1024];

	newtio.c_cc[VMIN] = 0;
	newtio.c_cc[VTIME] = 0;
	tcsetattr(fd,TCSANOW,&newtio);
	
	/* this should not block */
	count = read(fd, buffer, 128);
	printf("made it past no block\n");

	newtio.c_cc[VMIN] = 0;
	newtio.c_cc[VTIME] = 10;
	tcsetattr(fd,TCSANOW,&newtio);

	/* should block for 1 sec */
	count = read(fd, buffer, 128);
	printf("made it past block for 1 sec\n");

	newtio.c_cc[VMIN] = 10;
	newtio.c_cc[VTIME] = 0;
	tcsetattr(fd,TCSANOW,&newtio);

	/* try select with timeout */
	fd_set readfds;
	struct timeval tv;

	FD_SET(fd, &readfds);

	tv.tv_sec = 0;
	tv.tv_usec = 0;

	/* should return immediately because timeout is set to 0 */
	select(fd + 1, &readfds, NULL, NULL, &tv);
	printf("returned from select with timeout = 0\n");

	tv.tv_sec = 1;
	tv.tv_usec = 0;

	/* should return immediately because timeout is set to 0 */
	select(fd + 1, &readfds, NULL, NULL, &tv);
	printf("returned from select with 1s timeout\n");

	/* should block forever because timeout is set to NULL */
	select(fd + 1, &readfds, NULL, NULL, NULL);
	printf("should never be here -- should block forever\n");

	/* this should block forever until 10 chars have been received */
	count = read(fd, buffer, 128);
	printf("should never be here -- should block forever\n");
}


