/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 14:19:48 by kallard           #+#    #+#             */
/*   Updated: 2020/10/22 20:56:52 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
