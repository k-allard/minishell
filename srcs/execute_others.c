/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_others.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 19:35:15 by kallard           #+#    #+#             */
/*   Updated: 2020/10/30 18:16:44 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*find_path(char *argv, t_list *envs)
{
	int			i;
	char		*tmp;
	char		*new_path;
	char		**paths;
	struct stat	s;

	if (!(tmp = get_env_value("PATH", envs)))
		return (NULL);
	paths = ft_split(tmp, ':');
	i = -1;
	while (paths[++i])
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
