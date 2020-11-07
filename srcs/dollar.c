/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 14:19:48 by kallard           #+#    #+#             */
/*   Updated: 2020/10/23 17:23:02 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** $? 
*/

int		print_exit_status(char *line)
{
	if (line[0] == '$' && line[1] == '?')
	{
		ft_putstr_fd(ft_itoa(g_exit_value), 1);
		ft_putendl_fd(": command not found", 1);
		return (1);
	}
	return (0);
}

/*
** takes one argument where $ was found and returns it with variable value inserted
*/

char *insert_variable(char *argv, t_list *envs)
{
	int		i;
	int		start;
	char	*tmp[4];

	i = -1;
	start = 0;
	while (argv[++i])
	{
		if (argv[i] == '$' || argv[i + 1] == '\0')
		{
			if (start == 0)
			{
				tmp[3] = ft_substr(argv, start, i);
				start = i + 1;
				continue ;
			}
			tmp[0] = ft_substr(argv, start, i - start + 1);
			tmp[1] = ft_strdup(get_env_value(tmp[0], envs));
			tmp[2] = ft_strjoin(tmp[3], tmp[1]);
			free(tmp[3]);
			tmp[3] = tmp[2];
			start = i + 1;
		}
	}
	return (tmp[3]);
}
