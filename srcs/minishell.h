/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 22:38:29 by kallard           #+#    #+#             */
/*   Updated: 2020/10/19 19:30:19 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>					//	этот инклюд нужен, но не забыть потом заменить все оригинальные принтэфы на ft_ (если будут)



/*
** Глабальные переменные
*/
// t_msh			g_msh;				//основная структура: global minishell
char			**g_envp;			//массив переменных окружения
int				g_exit_value;
typedef struct	s_env
{
	char		*key;
	char		*value;
}				t_env;


t_list			*get_envs(int argc, char **argv, char **envp);
void			write_prompt();

int				deal_with_input(char **line);
char			**get_comands(char *line);
void			execute_comands(char *line, t_list *envs);

int				exec_builtins(char *line, t_list *envs);
//cd
void			command_echo(char **argv);
void			command_pwd(void);
void			command_env(t_list *envs);
//export
//unset
void			command_exit(char **argv);

#endif
