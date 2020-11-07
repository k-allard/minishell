/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 22:24:09 by kallard           #+#    #+#             */
/*   Updated: 2020/10/31 15:40:08 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		if_str_number(char *str)
{
	int	i;
	int sign;
	int len;
	int len_max;

	i = 0;
	sign = 1;
	if (str[i] == '-')
	{
		i++;
		sign = -1;
	} else
	if (str[i] == '+')
	{
		i++;
		sign = 1;
	}
	res = 0;
	while (str[i] && (len == 0))
		len = !(ft_isdigit(str[i++]));
	if(len != 0)
		return (0);

	len = ft_strlen(str);
	len_max = ft_strlen("9223372036854775807");
	if((sign == 1 && len > len_max) || (sign == -1 && len > len_max+1))
		return (0);
	if((sign == 1 && len == len_max && ft_strncmp("9223372036854775807", str, len_max) < 0) ||
			(sign == -1 && len == len_max+1 && ft_strncmp("-9223372036854775808", str, len_max) < 0))
		return (0);
	return (1);
}

int			command_exit(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	ft_putendl_fd("exit", 2);
	if (i == 1)
		exit(g_exit_value);
	else if (i == 2 && if_str_number(argv[1]))
	{
		exit((unsigned char)ft_atoi(argv[1]));
	}
	else if (i > 2 && if_str_number(argv[1]))
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return (1);
	}
	else
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit (255);
	}
}
