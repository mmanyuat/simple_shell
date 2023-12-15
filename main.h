#ifndef MAIN_H
#define MAIN_H

char **print_token(char *cmd, char *delimiter);
void execute_cmd(char *cmd);
void free_argv(char **argv);

#endif
