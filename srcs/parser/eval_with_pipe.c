/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_with_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 19:18:06 by kallard           #+#    #+#             */
/*   Updated: 2020/11/09 19:18:07 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../minishell.h"

static int	parent_waiting(pid_t *pid, int *res, int *file_pipes)
{
	int	status[2];

	waitpid(pid[0], &(status[0]), WNOHANG);
	if (WIFEXITED(status[0]))
		res[0] = WEXITSTATUS(status[0]);
	close(file_pipes[1]);
	waitpid(pid[1], &(status[1]), 0);
	if (WIFEXITED(status[1]))
		res[1] = WEXITSTATUS(status[1]);
	else
		res[1] = -1;
	return (res[1]);
}

static void	eval_left_pipe_end(int *res, int *file_pipes, \
	t_list_lexema *one_command_lexemas, t_list_env *envs)
{
	close(file_pipes[0]);
	dup2(file_pipes[1], STDOUT_FILENO);
	close(file_pipes[1]);
	if ((res[0] = eval_without_pipe(one_command_lexemas, envs)) < 0)
		unexpected_error_exit(0);
	exit(res[0]);
}

static void	eval_right_pipe_end(int *res, int *file_pipes, \
			t_list_lexema *lexema_chain, t_list_env *envs)
{
	close(file_pipes[1]);
	dup2(file_pipes[0], STDIN_FILENO);
	close(file_pipes[0]);
	if ((res[1] = eval_with_pipe_or_without(lexema_chain, envs)) < 0)
		unexpected_error_exit(0);
	exit(res[1]);
}

int			eval_with_pipe(t_list_lexema *lexema_chain, t_list_env *envs)
{
	t_list_lexema	*one_command_lexemas;
	int				file_pipes[2];
	pid_t			pid[2];
	int				res[2];

	one_command_lexemas = get_next_lexema_chain(&lexema_chain, \
	lexema_type_pipe);
	if (pipe(file_pipes) < 0)
		unexpected_error_exit(1);
	pid[0] = fork();
	if (pid[0] < 0)
		unexpected_error_exit(1);
	if (pid[0] == 0)
		eval_left_pipe_end(res, file_pipes, one_command_lexemas, envs);
	else
	{
		pid[1] = fork();
		if (pid[1] < 0)
			unexpected_error_exit(1);
		if (pid[1] == 0)
			eval_right_pipe_end(res, file_pipes, lexema_chain, envs);
		else
			return (parent_waiting(pid, res, file_pipes));
	}
	return (-1);
}
