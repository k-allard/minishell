/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 22:24:09 by kallard           #+#    #+#             */
/*   Updated: 2020/10/19 16:20:58 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		if_str_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (0);
	return (1);
}

void			command_exit(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	if (i == 1)
	{
		ft_putendl_fd("exit", 1);
		exit(EXIT_SUCCESS);
	}
	else if (i == 2 && if_str_number(argv[1]))
	{
		exit(ft_atoi(argv[1]));
	}
	else if (i > 2 && if_str_number(argv[1]))
		ft_putendl_fd("bash: exit: too many arguments", 1);
	else
	{
		ft_putstr_fd("bash: exit: numeric argument required", 1);
		exit(2);
	}
}
