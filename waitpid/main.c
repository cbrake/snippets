#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

// this works just fine

int main(void)
{
	int status;
	pid_t pid, pidr;

	//
	pid = fork();

	if (!pid)
	{
		// child
		printf("child is sleeping\n");
		//sleep(10);
		return 25;
	}

	sleep(5);

	printf("Child process is %i\n", pid);

	pidr = wait(&status);

	if (pidr == -1)
		perror("wait");

	if (WIFEXITED (status))
		printf("Normatl term with exit status = %d\n", WEXITSTATUS(status));

	if (WIFSIGNALED (status))
		printf("signaled = %d\n", WEXITSTATUS(status));
}

