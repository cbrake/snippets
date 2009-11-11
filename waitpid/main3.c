#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <glib.h>

// this works just fine

int main(void)
{
	int status;
	pid_t pid, pidr;
	int ret;
	int err;
	char c;

	//
	gchar *args[] = {"/bin/sleep", "5", NULL };

	// child
	printf("launching sleep 5\n");
	ret = g_spawn_async_with_pipes(NULL, args, NULL, 0, NULL, NULL, &pid, NULL, NULL, &err, NULL);
	if (ret == FALSE) {
		perror("g_spawn_async");
		exit(-1);
	}

	printf("Child process is %i\n", pid);

	while(1) {
		ret = read(err, &c, 1);
		g_debug("read %i", ret);
		if (ret <= 0) {
			g_debug("read err, ret = %i");
			break;
		}
	}

	if (WIFEXITED (status))
		printf("Normatl term with exit status = %d\n", WEXITSTATUS(status));

	if (WIFSIGNALED (status))
		printf("signaled = %d\n", WEXITSTATUS(status));
}

