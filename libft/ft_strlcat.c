/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 12:16:06 by kallard           #+#    #+#             */
/*   Updated: 2020/05/19 00:15:23 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Adds the src string --> to the dest string
** Overwrites the terminating null byte at the end of dest
** Guarantees to NUL-terminate the result
** Return the initial length of dst plus the length of src
*/

size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
{
	size_t i;
	size_t src_len;
	size_t dest_len;

	i = 0;
	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (dest_len >= destsize)
		return (destsize + src_len);
	while (src[i] && dest_len + i < destsize - 1)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}
