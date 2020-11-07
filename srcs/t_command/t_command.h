#ifndef FT_MINISHELL_T_COMMAND_H
#define FT_MINISHELL_T_COMMAND_H

#include "../minishell.h"


typedef struct s_command
{
    t_lexema *name;
    t_lexema **arguments;
    t_stream **streams;
    struct s_command *command_prev;
    struct s_command *command_next;
} t_command;

t_command* t_command_init();
void t_command_free(t_command *command);


#endif //FT_MINISHELL_T_COMMAND_H
