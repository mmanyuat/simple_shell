#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * execute_cmd -function to exrcute the cmd
 * @cmd:the command
 * Return:nothing
 */

void execute_cmd(char *cmd)
{
	char **argv;
	int status, exit_status;
	pid_t my_pid;

	argv = print_token(cmd, " \t\n");
	my_pid = fork();
	if (my_pid == -1)
	{
	perror("fork_error");
	free(argv);
	_exit(EXIT_FAILURE);
	}
	if (my_pid == 0)
	{
	execve(argv[0], argv, NULL);
	perror("error");
	free(argv);
	}
	else
	{
	wait(&status);
	if (WIFEXITED(status))
	{
	exit_status = WEXITSTATUS(status);

	if (exit_status != 0)
	{
		fprintf(stderr, "./shell: %s: Cmd failed %d\n", argv[0], exit_status);
	}
	}
	else if (WIFSIGNALED(status))
	{
	fprintf(stderr, "./shell: %s: cmd failed %d\n", argv[0], WTERMSIG(status));
	}
	free(argv);
	}
}
/**
 * main - function to build mini shell
 * Return: nothing
 */

int main(void)
{
	char *cmd = NULL;
	size_t n = 0;
	int length = 0;

	while (1)
	{
	const char *message = "$ Majesty, your commands: ";

	write(1, message, strlen(message));
	length = getline(&cmd, &n, stdin);
	if (length == -1)
	{
	perror("getline");
	free(cmd);
	_exit(EXIT_FAILURE);
	}
	if (length == 1)
	{
	free(cmd);
	_exit(0);
	}
	execute_cmd(cmd);
	free(cmd);
	}
	return (0);
}


