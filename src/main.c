#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	/**
	 * execve(2) call on an existing file.
	 */
	pid_t child = fork();
	if (child == 0) {
		execve("./say-something.sh", NULL, NULL);
		perror("execve ./say-something.sh");
		fprintf(stderr, "If this is printed, then ./say-something.sh is not an executable file.\n");
	}

	if (child == -1) {
		perror("fork 0");
		return -1;
	}

	int wstatus;
	pid_t after_wait = waitpid(child, &wstatus, 0);

	if (after_wait == -1) {
		perror("waitpid 0");
		return -1;
	}
	
	/**
	 * execve(2) call on a directory.
	 */
	child = fork();
	if (child == 0) {
		execve("./this-is-a-directory", NULL, NULL);
		perror("execve ./this-is-a-directory");
	}

	if (child == -1) {
		perror("fork 1");
		return -1;
	}

	after_wait = waitpid(child, &wstatus, 0);

	if (after_wait == -1) {
		perror("waitpid 1");
		return -1;
	}

	return 0;
}

