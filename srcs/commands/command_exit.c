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

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (0);
	return (1);
}

int				command_exit(char **argv, int i)
{
	i = 0;
	while (argv[i])
		i++;
	ft_putendl_fd("exit", 2);
	if (i == 1)
		exit(EXIT_SUCCESS);
	else if (i == 2 && if_str_number(argv[1]))
	{
		if (ft_atoi(argv[1]) >= 0)
			exit(ft_atoi(argv[1]));
		else
			exit(252);
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
		exit(255);
	}
}
