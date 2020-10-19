/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 22:38:29 by kallard           #+#    #+#             */
/*   Updated: 2020/10/19 13:08:05 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>					//	этот инклюд нужен, но не забыть потом заменить все оригинальные принтэфы на ft_ (если будут)



/*
** Глабальные переменные
*/
t_msh			g_msh;				//основная структура: global minishell
char			**g_envp;			//массив переменных окружения
int				g_exit_value;
typedef struct	s_env
{
	char		*key;
	char		*value;
}				t_env;


t_list		*get_envs(int argc, char **argv, char **envp);
void			write_prompt();

#endif
