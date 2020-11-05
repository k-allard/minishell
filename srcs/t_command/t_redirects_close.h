#ifndef FT_MINISHELL_T_REDIRECTS_CLOSE_H
#define FT_MINISHELL_T_REDIRECTS_CLOSE_H

#include "../minishell.h"


typedef struct s_command
{
    t_list_lexema *command_with_args;
    int stdout_fd;
    int stdin_fd;
} t_command;

t_command* t_command_init();
void t_command_free(t_command *command);


#endif //FT_MINISHELL_T_REDIRECTS_CLOSE_H
