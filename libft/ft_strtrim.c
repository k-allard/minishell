/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 13:57:54 by kallard           #+#    #+#             */
/*   Updated: 2020/05/11 22:17:35 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Removes chars specified in ’set’ from the beginning and the end of string s1.
** Allocates and returns a copy of s1 modified.
*/

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	i;
	unsigned int	end;
	size_t			setlen;
	unsigned char	trim_hashmap[5000];

	if (!s1 || !set)
		return (NULL);
	setlen = ft_strlen(set);
	if (!setlen || !ft_strlen(s1))
		return (ft_strdup(s1));
	ft_bzero(trim_hashmap, 5000);
	i = 0;
	while (i < setlen)
		trim_hashmap[(unsigned int)set[i++]] = 1;
	i = 0;
	end = ft_strlen(s1) - 1;
	while (s1[i] && trim_hashmap[(unsigned int)s1[i]])
		i++;
	while (end > i && trim_hashmap[(unsigned int)s1[end]])
		end--;
	return (ft_substr(s1, i, end - i + 1));
}
