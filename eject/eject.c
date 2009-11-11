#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define CDROMEJECT                0x5309  /* Ejects the cdrom media */

int main(int argc, char **argv)
{
	unsigned long flags;
	const char *device = "/dev/sr0";
	int dev, cmd;

	dev = open(device, O_RDONLY|O_NONBLOCK);
	cmd = CDROMEJECT;

	ioctl(dev, cmd);

	close(dev);

	return 0;
}
