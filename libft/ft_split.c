/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 13:56:02 by kallard           #+#    #+#             */
/*   Updated: 2020/05/20 23:54:30 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_freeresult(char ***result)
{
	int	i;

	i = 0;
	while ((*result)[i])
		free((*result)[i++]);
	free(*result);
}

static int	ft_token_count(char const *str, char c)
{
	int tok;
	int i;

	if (c == '\0')
		return (1);
	tok = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c && i > 0 && str[i - 1] != c)
			tok++;
		i++;
	}
	if (i > 0 && !str[i] && str[i - 1] != c)
		tok++;
	return (tok);
}

static void	ft_split_tokens(char *scopy, char c, char ***result)
{
	int i;
	int tok;
	int end;
	int i_next;

	i_next = 0;
	i = 0;
	tok = 0;
	while (scopy[i])
	{
		end = i + 1;
		while (scopy[end] != c && scopy[end] != '\0')
			end++;
		i_next = scopy[end] > 0 ? (end + 1) : end;
		scopy[end] = '\0';
		if (!((*result)[tok++] = ft_strdup(&scopy[i])))
		{
			ft_freeresult(result);
			return ;
		}
		while (c != '\0' && scopy[i_next] == c)
			i_next++;
		i = i_next;
	}
}

/*
** Splits ’s’ using the character ’c’ as a delimiter.
** Allocates and returns an array of strings obtained.
*/

char		**ft_split(char const *s, char c)
{
	char	*scopy;
	char	**result;
	int		counttok;
	char	set[2];

	if (!s)
		return (NULL);
	set[0] = c;
	set[1] = '\0';
	scopy = ft_strtrim(s, set);
	counttok = ft_token_count(s, c);
	if (!(result = (char **)malloc((counttok + 1) * sizeof(char *))))
		return (NULL);
	result[counttok] = NULL;
	ft_split_tokens(scopy, c, &result);
	free((void *)scopy);
	return (result);
}
