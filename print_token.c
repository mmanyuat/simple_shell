#include "main.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * print_token - function to tokenize a command
 * @cmd:the command
 * @delimiter:the delim
 * Return:the argv
 */

char **print_token(char *cmd, char *delimiter)
{
	char **argv;
	char *cpycmd = strdup(cmd);
	char *cpycmd2 = strdup(cmd);
	int len_token = 0;
	char *token;
	int i = 0;

	token = strtok(cpycmd, delimiter);
	while (token != NULL)
	{
	len_token++;
	token = strtok(NULL, delimiter);
	}
	argv = malloc((len_token + 1) * sizeof(char *));
	token = strtok(cpycmd2, delimiter);
	while (token != NULL)
	{
	argv[i] = malloc((strlen(token) + 1) * sizeof(char));
	strcpy(argv[i], token);
	token = strtok(NULL, delimiter);
	i++;
	}
	argv[i] = NULL;
	free(cpycmd);
	free(cpycmd2);
	return (argv);

}

/**
 * main - function to free argv
 * Return:Nothing
 */

void free_argv(char **argv)
{
	int i;

	if (argv == NULL)
	return;

	for (i = 0; argv[i] != NULL; i++)
	{
	free(argv[i]);
	}
	free(argv);
}
