/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 15:50:07 by kallard           #+#    #+#             */
/*   Updated: 2020/09/05 15:50:11 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Copies chars from the string src --> to dest.
** NUL-terminates the result.
** Returns dest.
*/

char	*ft_strcpy(char *dest, const char *src)
{
	int i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
