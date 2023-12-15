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
 * non_intereactive - function to build mini shell
 * Return: nothing
 */

void non_intereactive(void)
{
	char *cmd = NULL;
	size_t n = 0;
	ssize_t length;

	while ((length = getline(&cmd, &n, stdin)) != -1)
	{
	cmd[strcspn(cmd, "\n")] = '\0';
	execute_cmd(cmd);
	free(cmd);
	cmd = NULL;
	n = 0;
	}
	free(cmd);
}

/**
 * main - main function
 * @argc: argument count
 * @argv: argument vector
 * Return:nothing
 */

int main(int argc, char *argv[])
{
	(void)argv;
	if (argc > 1)
	{
	non_intereactive();
	}
	else
	{
	char *cmd = NULL;
	size_t n = 0;
	int length = 0;

	while (1)
	{
	const char *message = "#cisfun$: ";

	write(1, message, 10);
	length = getline(&cmd, &n, stdin);
	if (length == -1)
	{
	perror("getline");
	free(cmd);
	_exit(EXIT_FAILURE);
	}
	else
	{
	cmd[strcspn(cmd, "\n")] = '\0';
	if (strcmp(cmd, "exit") == 0)
	{
	break;
	}
	execute_cmd(cmd);
	free(cmd);
	cmd = NULL;
	n = 0;
	}
	}
	free(cmd);
	}
	return (0);
}


