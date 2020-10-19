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

# include "minishell.h"

void	handle_signal(int signo)
{
	int		status;

	if (signo == SIGINT)    //Ctrl-C
	{
		//ничего стереть не надо?
		ft_putstr_fd("\n", 1);
		write_prompt();
		g_exit_value = 1;
	}
	// else if (signo == SIGQUIT)  //Ctrl-\
	// {

	// }
	return ;
}
