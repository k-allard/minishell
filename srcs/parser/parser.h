#ifndef FT_MINISHELL_PARSER_H
#define FT_MINISHELL_PARSER_H

# include "../minishell.h"

enum COMMANDS_INDEX
{
	COMMAND_EXTERNAL = 0,
	COMMAND_CD,
	COMMAND_ECHO,
	COMMAND_EXPORT,
	COMMAND_EXIT,
	COMMAND_ENV,
	COMMAND_PWD,
	COMMAND_UNSET,
	NONE_COMMAND
} typedef E_COMMAND;

t_list_lexema *get_lexema_list(char *commandline);
void parser_debug_print_lexema_list(t_list_lexema *lexema_list);

void check_marker_syntaxis(t_list_lexema *lexema_list);
t_list_lexema *get_next_lexema_chain(t_list_lexema **lexema_list, t_lexema_type delimeter);
void eval_vars_and_unescape_$_in_lexema_chain(t_list_lexema *lexema_chain, int argc, char **argv, t_list_env *envs);

t_command *get_command(t_list_lexema *one_command_lexemas);

int parser(char *commandline, int argc, char **argv, t_list_env *envs);
int eval_with_pipe_or_without(t_list_lexema *lexema_chain, t_list_env *envs);
int eval_with_redirect_or_without(t_list_lexema *one_command_lexemas, t_list_env *envs);
int eval_with_fork_or_without(t_list_lexema *one_command_lexemas, t_list_env *envs);
int exec_external_or_builtin_command(t_list_lexema *lexema_chain, t_list_env *envs);

E_COMMAND get_command_type(char *command_name);

#endif //FT_MINISHELL_PARSER_H
