#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

// this works just fine

int main(void)
{
	int status;
	pid_t pid, pidr;
	int ret;

	//
	pid = fork();

	const char *args[] = {"/bin/sleep", "5", NULL };

	if (!pid)
	{
		// child
		printf("launching sleep 5\n");
		ret = execvp("/bin/sleep", args);
		if (ret == -1) {
			perror("execvp");
			exit(-1);
		}
	}

	printf("Child process is %i\n", pid);

	pidr = waitpid(pid, &status, 0);

	if (pidr == -1)
		perror("wait");

	if (WIFEXITED (status))
		printf("Normatl term with exit status = %d\n", WEXITSTATUS(status));

	if (WIFSIGNALED (status))
		printf("signaled = %d\n", WEXITSTATUS(status));
}

