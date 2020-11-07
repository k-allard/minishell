/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 22:43:25 by kallard           #+#    #+#             */
/*   Updated: 2020/05/09 11:45:30 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Compares byte strings, both assumed to be n bytes long.
** Returns zero if they are identical.
*/

int	ft_memcmp(const char *str1, const char *str2, size_t n)
{
	unsigned int	i;

	i = 0;
	while ((i < n) && ((unsigned char *)str1)[i] == ((unsigned char *)str2)[i])
		i++;
	if (i == n)
		return (0);
	else
		return (((unsigned char *)str1)[i] - ((unsigned char *)str2)[i]);
}
