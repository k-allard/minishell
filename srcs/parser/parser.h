#ifndef FT_MINISHELL_PARSER_H
#define FT_MINISHELL_PARSER_H

# include "../minishell.h"



t_list_lexema *get_lexema_list(char *commandline);
void parser_debug_print_lexema_list(t_list_lexema *lexema_list);

void check_marker_syntaxis(t_list_lexema *lexema_list);
t_list_lexema *get_next_lexema_chain(t_list_lexema **lexema_list, t_lexema_type delimeter);
void eval_vars_and_unescape_$_in_lexema_chain(t_list_lexema *lexema_chain, int argc, char **argv, t_list_env *envs);

t_command *get_command(t_list_lexema *one_command_lexemas);

int eval_lexema_chain(t_list_lexema *lexema_chain, t_list_env *envs);
int parser(char *commandline, int argc, char **argv, t_list_env *envs);

#endif //FT_MINISHELL_PARSER_H
