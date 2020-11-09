/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_others.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 19:35:15 by kallard           #+#    #+#             */
/*   Updated: 2020/11/10 00:03:42 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_absolute_path(char *path)
{
	struct stat	s;

	if (stat(path, &s) == 0)
		return (1);
	else
		return (0);
}

char		*find_path(char *argv, t_list *envs)
{
	int			i;
	char		*tmp;
	char		*new_path;
	char		**paths;
	struct stat	s;

	if (is_absolute_path(argv))
		return (argv);
	tmp = get_env_value("PATH", envs);
	paths = ft_split(tmp, ':');
	i = -1;
	while (paths && paths[++i])
	{
		tmp = ft_strjoin("/", argv);
		new_path = ft_strjoin(paths[i], tmp);
		free(tmp);
		if (stat(new_path, &s) == 0)
		{
			free_double_array(paths);
			return (new_path);
		}
		free(new_path);
	}
	free_double_array(paths);
	return (NULL);
}
