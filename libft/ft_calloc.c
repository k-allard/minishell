/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 15:39:02 by kallard           #+#    #+#             */
/*   Updated: 2020/05/09 11:48:06 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Allocates memory for count objects that are size bytes each.
** Fills the allocated memory with zeros.
** Returns a pointer to the allocated memory.
*/

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;

	if (!(ptr = (char *)malloc(count * size)))
		return (NULL);
	return (ft_memset(ptr, 0, count * size));
}
