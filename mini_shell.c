#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - function to build mini shell
 * Return: nothing
 */

int main(void)
{
	char *cmd = NULL;
	size_t n = 0;
	int length = 0;
	char **argv;
	pid_t my_pid;
	int status;

	while (1)
	{
	const char *message = "$ Majesty, your commands: ";

	write(1, message, strlen(message));
	length = getline(&cmd, &n, stdin);
	if (length == 1)
	{
	free(cmd);
	exit(0);
	}
	argv = print_token(cmd, " \t\n");
	my_pid = fork();
	if (my_pid == -1)
	{
	perror("error");
	exit(EXIT_FAILURE);
	}
	if (my_pid == 0)
	{
	if (execve(argv[0], argv, NULL) == -1)
	{
	perror("error");
	}
	}
	else
	{
	wait(&status);
	}
	}
	return (0);
}


