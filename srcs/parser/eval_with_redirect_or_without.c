/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_with_redirect_or_without.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 22:47:22 by kallard           #+#    #+#             */
/*   Updated: 2020/11/09 01:37:56 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

static int	apply_redirects(t_list_lexema *redirect, t_redirects *redirects_fd)
{
	t_list_lexema	*one_redirect;
	int				r;

	while ((one_redirect = get_next_redirect(&redirect, &r)) && r == 0)
	{
		if (one_redirect->lexema->lexema_type == lexema_type_redirect_to)
		{
			r = redir_stdout(redirects_fd, one_redirect->next->lexema->string, \
			O_WRONLY | O_CREAT | O_TRUNC);
		}
		else if (one_redirect->lexema->lexema_type == \
		lexema_type_redirect_to_append)
		{
			r = redir_stdout(redirects_fd, one_redirect->next->lexema->string, \
			O_WRONLY | O_CREAT | O_APPEND);
		}
		else if (one_redirect->lexema->lexema_type == lexema_type_redirect_from)
		{
			r = redir_stdin(redirects_fd, one_redirect->next->lexema->string, \
			O_RDONLY);
		}
	}
	return (r);
}

static void	split_command_with_redirect(t_list_lexema *all,\
t_list_lexema **cmd, t_list_lexema **redirect, int is_find)
{
	t_list_lexema *prev;
	t_list_lexema *current;

	prev = NULL;
	current = all;
	while (current && !is_find)
	{
		if (is_redirect(current->lexema))
		{
			is_find = 1;
			if (prev == NULL)
				*cmd = NULL;
			else
			{
				prev->next = NULL;
				*cmd = all;
			}
			*redirect = current;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

static int	eval_without_redirect(t_list_lexema *command_lexemas,\
t_list_env *envs)
{
	int	res;

	res = eval_with_fork_or_without(command_lexemas, envs);
	return (res);
}

static int	eval_with_redirect(t_list_lexema *one_command_lexemas,\
t_list_env *envs)
{
	int				res;
	t_list_lexema	*redirect_only;
	t_list_lexema	*command_only;
	t_redirects		redirects_fd;

	redirects_fd.stdout_original = -1;
	redirects_fd.stdin_original = -1;
	redirects_fd.stdin_fd = -1;
	redirects_fd.stdout_fd = -1;
	split_command_with_redirect(one_command_lexemas, &command_only,\
	&redirect_only, 0);
	res = apply_redirects(redirect_only, &redirects_fd);
	if (command_only != NULL && res == 0)
		res = eval_with_fork_or_without(command_only, envs);
	if ((t_redirects_close(&redirects_fd) == -1) && (res == 0))
		res = 1;
	return (res);
}

int			eval_with_redirect_or_without(t_list_lexema *one_command_lexemas,\
t_list_env *envs)
{
	int res;

	if (is_redirect_exist(one_command_lexemas))
		res = eval_with_redirect(one_command_lexemas, envs);
	else
		res = eval_without_redirect(one_command_lexemas, envs);
	return (res);
}
