/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwindom <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 15:54:28 by cwindom           #+#    #+#             */
/*   Updated: 2020/05/23 15:54:30 by cwindom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*search(const char *set, char c)
{
	char	*str;
	int		n;

	n = (int)ft_strlen(set);
	str = (char *)set;
	while (n--)
	{
		if (*str == c)
			return (str);
		str++;
	}
	return (NULL);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	size_t	left;
	size_t	right;

	left = 0;
	right = ft_strlen(s1);
	if (!(s1 && set))
		return (0);
	if (*set == '\0')
		return (ft_strdup(s1));
	while (s1[left] && search(set, s1[left]))
		left++;
	while (s1[right - 1] && search(set, s1[right - 1]))
		right--;
	if (right - left > right)
		return (ft_substr(s1, left, 0));
	return (ft_substr(s1, left, right - left));
}
