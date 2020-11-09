/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwindom <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 14:28:49 by cwindom           #+#    #+#             */
/*   Updated: 2020/11/09 14:28:50 by cwindom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

int			external_command_exist(char *command_name, \
			t_list_lexema *lexema_chain, t_list_env *envs)
{
	int		res;
	char	**env;
	char	**args;

	args = lexema_chain_2_argv(lexema_chain);
	env = list_env_2_env(envs);
	if ((res = execve(command_name, args, env)) < 0)
	{
		if (errno == ENOENT)
		{
			ft_putstr_fd(command_name, STDERR_FILENO);
			ft_putendl_fd(": command not found", STDERR_FILENO);
			res = 127;
		}
		else
			res = errno;
	}
	free_double_array(args);
	free_double_array(env);
	return (res);
}

static int	exit_code(int code, t_list_lexema *lexema_list)
{
	if (lexema_list != NULL)
		lexema_chain_free(lexema_list);
	g_exit_value = code;
	return (code);
}

int			parser(char *commandline, t_args_struct *args_struct)
{
	t_list_lexema	*lexema_list;
	t_list_lexema	*lexema_chain;
	int				res;

	lexema_list = get_lexema_list(commandline, &res);
	if (res)
		return (exit_code(res, lexema_list));
	if (lexema_list == NULL)
		return (0);
	res = check_marker_syntaxis(lexema_list);
	if (res)
		return (exit_code(res, lexema_list));
	while ((lexema_chain = get_next_lexema_chain(&lexema_list,\
	lexema_type_semicolon)))
	{
		eval_vars_unesc_dol_in_lex_chain(lexema_chain, args_struct);
		join_lexemas_without_spaces(lexema_chain);
		remove_empty_elements(&lexema_chain);
		if (lexema_chain != NULL)
		{
			res = eval_with_pipe_or_without(lexema_chain, args_struct->envs);
			lexema_chain_free(lexema_chain);
		}
	}
	return (res);
}
