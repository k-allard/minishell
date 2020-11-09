/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_with_redirect_or_without_3.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwindom <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 04:24:23 by cwindom           #+#    #+#             */
/*   Updated: 2020/11/09 04:24:26 by cwindom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

int	redir_stdout(t_redirects *redirects_fd, char *filename, int flags)
{
	int res;

	if (redirects_fd->stdout_fd == -1)
		redirects_fd->stdout_original = dup(STDOUT_FILENO);
	if ((res = open_redirect_fd(&(redirects_fd->stdout_fd), STDOUT_FILENO, \
	filename, flags)) == 0)
		if ((res = dup2(redirects_fd->stdout_fd, STDOUT_FILENO)) != -1)
			res = 0;
	if (res != 0)
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	return (res);
}

int	redir_stdin(t_redirects *redirects_fd, char *filename, int flags)
{
	int	res;

	if (redirects_fd->stdin_fd == -1)
		redirects_fd->stdin_original = dup(STDIN_FILENO);
	res = -1;
	if (0 == open_redirect_fd(&(redirects_fd->stdin_fd), STDIN_FILENO, \
	filename, flags))
		if (-1 != dup2(redirects_fd->stdin_fd, STDIN_FILENO))
			res = 0;
	if (res != 0)
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	return (res);
}

int	open_redirect_fd(int *current_fd, int std_fd, \
char *filename, int flags)
{
	int res;

	if ((res = close(std_fd)) == 0)
	{
		*current_fd = open(filename, flags, 0644);
		if (*current_fd == -1)
		{
			ft_putstr_fd("Error by start redirect with file: ", STDERR_FILENO);
			ft_putendl_fd(filename, STDERR_FILENO);
			res = -1;
		}
	}
	return (res);
}
