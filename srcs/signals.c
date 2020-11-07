/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 00:11:40 by kallard           #+#    #+#             */
/*   Updated: 2020/10/19 16:02:24 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	handle_signal(int signo)
{
	int		status;

	if (signo == SIGINT)
	{
		ft_putstr_fd("\b\b  \b\b", 1);
		ft_putstr_fd("\n", 1);
		write_prompt();
		//g_exit_value = 1;
	}
	else if (signo == SIGQUIT)
	{
		signo = wait(&status);
		//g_exit_value = status / 256;
		ft_putstr_fd("\b\b  \b\b", 1);
		//g_exit_value = 127;
		if (signo != -1)
			ft_putstr_fd("^\\Quit: 3\n", 1);
	}
	return ;
}

void	signals(void)
{
	signal(SIGINT, (void *)handle_signal);
	signal(SIGQUIT, (void *)handle_signal);
}
