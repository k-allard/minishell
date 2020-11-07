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

void	setup()
{
	signal(SIGINT, (void *)handle_signal);
	signal(SIGQUIT, (void *)handle_signal);
}

















/*
extern pid_t pid;

void		handler(int sig) //нужно только в my_signal
{
	if (sig == SIGINT)
	{
		write(1, "\b\b  \b\b", 6);
		write_prompt();
	}
	else if (sig == SIGQUIT)
	{
		write(1, "\b\b  \b\b", 6);
	}
}

void			my_signal(void) //положить в мейн перед функцией в которой гнл
{
	if ((signal(SIGINT, handler)) == SIG_ERR)
    {
        write_prompt();
        ft_putstr_fd(strerror(errno), 2);
		exit(-1);
    }
	if ((signal(SIGQUIT, handler)) == SIG_ERR)
    {
        write_prompt();
        ft_putstr_fd(strerror(errno), 2);
		exit(-1);
    }
}

void			print_signal(int s) //нужно где-то в запуске команд, подумать куда лучше добавить
{
	if (!WIFSIGNALED(s))
		return ;
	s = WTERMSIG(s);
	if (s == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		write_prompt();
	}
	else if (s == SIGQUIT) ////Ctrl- '\'
		ft_putstr_fd("Quit: ", 1);
	else if (s == SIGKILL)
		ft_putstr_fd("Killed: ", 1);
	if (s != SIGINT && s != SIGPIPE)
		ft_putnbr_fd(s, 1);
	if (s != SIGPIPE) //Ctrl-D
		ft_putendl_fd(NULL, 1);
}



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
*/