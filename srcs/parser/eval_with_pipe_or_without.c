/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_with_pipe_or_without.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 04:36:43 by cwindom           #+#    #+#             */
/*   Updated: 2020/11/09 19:18:45 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

int		is_pipe_in_lexema_chain(t_list_lexema *lexema_chain)
{
	int is_pipe;

	is_pipe = 0;
	while (lexema_chain && !is_pipe)
	{
		if (lexema_chain->lexema->lexema_type == lexema_type_pipe)
			is_pipe = 1;
		lexema_chain = lexema_chain->next;
	}
	return (is_pipe);
}

int		eval_without_pipe(t_list_lexema *lexema_chain, t_list_env *envs)
{
	return (eval_with_redirect_or_without(lexema_chain, envs));
}

void	unexpected_error_exit(int exit_flag)
{
	ft_putendl_fd("Error: command execution failed", STDERR_FILENO);
	if (exit_flag)
		exit(9);
}

int		eval_with_pipe_or_without(t_list_lexema *lexema_chain, \
		t_list_env *envs)
{
	int res;

	if (is_pipe_in_lexema_chain(lexema_chain))
		res = eval_with_pipe(lexema_chain_copy(lexema_chain), envs);
	else
		res = eval_without_pipe(lexema_chain, envs);
	g_exit_value = res;
	return (res);
}
