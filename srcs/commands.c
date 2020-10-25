/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 12:31:37 by kallard           #+#    #+#             */
/*   Updated: 2020/10/24 23:46:58 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			execute_commands(char *line, t_list *envs)
{
	// ft_putendl_fd("[We are in execute_commands]", 1);
	if (pipe_found(line))
		execute_pipes(line, envs);
	// else if (redirect_found(line))
	// 	exec_redirect(line, envs);
	else if (!print_exit_status(line) && !execute_builtins(line, envs))
		execute_others(line, envs);
}

int		syntax_error(char *line)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = ft_strtrim(line, " ");
	if (tmp[0] == ';')
	{
		free(tmp);
		return (1);
	}
	while (tmp[++i])
	{
		if (tmp[i] == ';' && tmp[i + 1] == ';')
		{
			free(tmp);
			return (1);
		}
	}
	free(tmp);
	return (0);
}

char			**get_comands(char *line)
{
	int		i;
	int		empty;
	char	*tmp;
	char	**comands;

	empty = 0;
	comands = ft_split(line, ';');
	i = -1;
	while (comands[++i])
	{
		tmp = ft_strtrim(comands[i], " ");
		empty = (!tmp || !(*tmp)) ? 1 : 0;
		free(comands[i]);
		!empty ? comands[i] = tmp : 0;
	}
	if (empty || syntax_error(line))
	{
		free(comands);
		ft_putendl_fd("syntax error near unexpected token `;'", 2);
		//free(line);
		return (NULL);
	}
	//free(line);
	return (comands);
}