/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 10:55:18 by kallard           #+#    #+#             */
/*   Updated: 2020/05/19 00:17:26 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Locates the 1st occurrence of the string to_find in the string str,
** where not more than len chars are searched.
*/

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t len2;

	if (!to_find[0])
		return ((char *)str);
	len2 = ft_strlen(to_find);
	while (*str && len >= len2)
	{
		if (*str == *to_find && ft_memcmp(str, to_find, len2) == 0)
			return ((char *)str);
		len--;
		str++;
	}
	return (0);
}
