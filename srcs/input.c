/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 12:17:10 by kallard           #+#    #+#             */
/*   Updated: 2020/10/23 14:54:57 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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