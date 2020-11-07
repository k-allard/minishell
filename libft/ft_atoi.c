/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 06:54:54 by kallard           #+#    #+#             */
/*   Updated: 2020/09/28 13:22:50 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Converts ASCII string to integer.
** Is intended to imitate the behaviour of original atoi,
** which has undef behavior if the value of the result cannot be represented.
*/

int			ft_atoi(char *str)
{
	unsigned long long	result;
	int					length_max;
	int					sign;
	int					i;

	result = 0;
	length_max = 19;
	sign = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		sign = (str[i++] == '-') ? -1 : 1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i++] - '0';
		if (length_max-- < 0)
			return ((sign == 1) ? -1 : 0);
		if (result >= LLMAX && sign == 1)
			return (-1);
		if (result > LLMAX && sign == -1)
			return (0);
	}
	return (sign * result);
}
