# include "../minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../t_lexema/t_lexema.h"
#include "../t_stream/t_stream.h"
#include "../t_command/t_command.h"
#include "parser.h"





int parser(char *commandline, int argc, char **argv, t_list_env	*envs)
{
    t_list_lexema *lexema_list;
    t_list_lexema *lexema_chain;
    int res;

    lexema_list = get_lexema_list(commandline);

//    ft_putstr_fd("«", STDERR_FILENO);
//    ft_putstr_fd(commandline, STDERR_FILENO);
//    ft_putstr_fd("»\n", STDERR_FILENO);
//    parser_debug_print_lexema_list(lexema_list);

    check_marker_syntaxis(lexema_list);

    while ((lexema_chain = get_next_lexema_chain(&lexema_list, lexema_type_semicolon)))
    {
        eval_vars_and_unescape_$_in_lexema_chain(lexema_chain, argc, argv, envs);
//		ft_putstr_fd("«After eval_vars_and_unescape_$_in_lexema_chain:»\n", STDERR_FILENO);
//		parser_debug_print_lexema_list(lexema_chain);
		remove_empty_elements(&lexema_chain);
//		ft_putstr_fd("«After remove_empty_elements:»\n", STDERR_FILENO);
//		parser_debug_print_lexema_list(lexema_chain);
        res = eval_with_pipe_or_without(lexema_chain, envs);
    }
    return res;
}