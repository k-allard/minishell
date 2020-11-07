/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 22:02:06 by kallard           #+#    #+#             */
/*   Updated: 2020/05/17 18:42:57 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Copies bytes from string src --> to non-overlapping string dst.
** If the char c occurs in src, the copy stops.
** Returns a pointer to the byte after the copy of c in dst.
** Otherwise, copies n bytes and returns NULL.
*/

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*dest_p;
	unsigned char	*src_p;

	if (!src && !dest)
		return (0);
	dest_p = (unsigned char *)dest;
	src_p = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dest_p[i] = src_p[i];
		if (src_p[i] == (unsigned char)(c))
			return ((void *)(dest + i + 1));
		i++;
	}
	return (NULL);
}
