/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_to_find.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:33:59 by kallard           #+#    #+#             */
/*   Updated: 2020/10/20 21:58:50 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int		pipe_found(char *line)
{
	while (*line)
		if (*line++ == '|')
			return (1);
	return (0);
}

int		redirect_found(char *line)
{
	while (*line)
	{
		if (*line == '>' || *line == '<')
			return (1);
        line++;
	}
	return (0);
}

int		dollar_found(char *line)
{
	while (*line)
		if (*line++ == '$')
			return (1);
	return (0);
}

int		quote_found(char *line)
{
	while (*line)
	{
		if (*line == '\'' || *line == '\"')
			return (1);
        line++;
	}
	return (0);
}
