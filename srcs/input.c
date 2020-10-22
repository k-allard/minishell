/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 12:17:10 by kallard           #+#    #+#             */
/*   Updated: 2020/10/22 14:19:31 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_argumentes(char *line, t_list *envs)
{
	int		i;
	char	**argv;

	if (!(argv = ft_split(line, ' ')))
		return (0);
	//случаи переменных:
	i = -1;
	while (argv[++i])
	{
		if (ft_strlen(argv[i]) > 1 && dollar_found(argv[i]))
			argv[i] = insert_variable(argv[i], envs);
	}
	//случаи кавычек:

	return (argv);
}

static void		catch_input(char **line)
{
	get_next_line(0, line); //???
}

int				deal_with_input(char **line)
{
	char	*tmp;

	catch_input(line);
	if (**line == '\n')
	{
		free(*line);
		return (0);
	}
	if (*line)
	{
		tmp = ft_strtrim(*line, " ");
		if (*line)
		{
			free(*line);
			*line = NULL;
		}
		*line = tmp;
	}
	return (1);
}