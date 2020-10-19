/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 00:11:40 by kallard           #+#    #+#             */
/*   Updated: 2020/10/18 16:26:06 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	handle_signal(int signo)
{
	int		status;

	if (signo == SIGINT)    //Ctrl-C
	{

	}
	else if (signo == SIGQUIT)  //Ctrl-\
	{

	}
	return ;
}
