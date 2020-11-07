/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 20:32:08 by kallard           #+#    #+#             */
/*   Updated: 2020/05/17 17:39:14 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Locates the first occurrence of char c in string s.
** Returns a pointer to it or NULL if it doesn't exist within n bytes.
*/

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int		i;
	unsigned const char	*p;

	p = (unsigned const char *)s;
	i = 0;
	while (i < n)
	{
		if ((unsigned char)(c) == (unsigned const char)(p[i]))
			return ((void *)(p + i));
		i++;
	}
	return (NULL);
}
