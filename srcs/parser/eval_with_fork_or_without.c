/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_with_fork_or_without.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 22:46:47 by kallard           #+#    #+#             */
/*   Updated: 2020/11/08 22:46:48 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "parser.h"

int	eval_without_fork(t_list_lexema *one_command_lexemas, t_list_env *envs)
{
	return (exec_external_or_builtin_command(one_command_lexemas, envs));
}

int	eval_with_fork(t_list_lexema *one_command_lexemas, t_list_env *envs)
{
	pid_t	pid;
	int		res;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("Could not fork\n", STDERR_FILENO);
		exit(10);
	}
	if (pid == 0)
	{
		if ((res = eval_without_fork(one_command_lexemas, envs)) < 0)
		{
			ft_putstr_fd("Error: unexpected error executing the command\n",\
			STDERR_FILENO);
			// parser_debug_print_lexema_list(one_command_lexemas);
		}
		exit(res);
	}
	else
	{
		waitpid(pid, &(status), 0);
		res = WIFEXITED(status) ? WEXITSTATUS(status) : -1;
		return (res);
	}
}

int	eval_with_fork_or_without(t_list_lexema *cmd, t_list_env *envs)
{
	t_command command_index;

	command_index = get_command_type(cmd->lexema->string);
	if (command_index == COMMAND_EXTERNAL)
		return (eval_with_fork(cmd, envs));
	else
		return (eval_without_fork(cmd, envs));
}
