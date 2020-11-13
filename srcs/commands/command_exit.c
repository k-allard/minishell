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

static int		if_str_number(char *str, int i, int s, int l)
{
	int m;

	if (str[i] == '-')
	{
		i++;
		s = -1;
	}
	else if (str[i] == '+')
	{
		i++;
		s = 1;
	}
	while (str[i] && (l == 0))
		l = !(ft_isdigit(str[i++]));
	if (l != 0)
		return (0);
	l = ft_strlen(str);
	m = ft_strlen("9223372036854775807");
	if ((s == 1 && l > m) || (s == -1 && l > m + 1))
		return (0);
	if ((s == 1 && l == m && ft_strncmp("9223372036854775807", str, m) < 0) ||
	(s == -1 && l == m + 1 && ft_strncmp("-9223372036854775808", str, m) < 0))
		return (0);
	return (1);
}

int				command_exit(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	ft_putendl_fd("exit", 2);
	if (i == 1)
		exit(g_exit_value);
	else if (i == 2 && if_str_number(argv[1], 0, 1, 0))
	{
		exit((unsigned char)ft_atoi(argv[1]));
	}
	else if (i > 2 && if_str_number(argv[1], 0, 1, 0))
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return (1);
	}
	else
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(255);
	}
}
