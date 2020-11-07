/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 22:54:18 by kallard           #+#    #+#             */
/*   Updated: 2020/05/18 22:55:11 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_memcpy_rev(void *dest, const void *src, size_t n)
{
	if (!src && !dest)
		return (0);
	while (n--)
	{
		((unsigned char *)dest)[n] = ((unsigned char *)src)[n];
	}
	return (dest);
}

/*
** Copies len bytes from string src --> to string dest.
** The two strings may overlap.
*/

void		*ft_memmove(void *dest, const void *src, size_t len)
{
	if (dest < src)
		return (ft_memcpy(dest, src, len));
	if (dest > src)
		return (ft_memcpy_rev(dest, src, len));
	return (dest);
}
