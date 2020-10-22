/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 22:38:29 by kallard           #+#    #+#             */
/*   Updated: 2020/10/22 00:15:52 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>					//	этот инклюд нужен, но не забыть потом заменить все оригинальные принтэфы на ft_ (если будут)
# include <dirent.h>


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

typedef struct	s_all
{
	int			argc;

	t_list		*envs;
}				t_all;

typedef struct	s_pipe
{
	char		*left_end;
	char		**argv;
}				t_pipe;

t_list			*get_envs(int argc, char **argv, char **envp);
void			write_prompt();

int				deal_with_input(char **line);
char			**get_comands(char *line);
char			**get_argumentes(char *line, t_list *envs);
void			execute_commands(char *line, t_list *envs, t_all all);

void			execute_pipes(char *line, t_list *envs, t_all all);
void			execute_others(char *line, t_list *envs);
int				execute_builtins(char *line, t_list *envs, t_all all);
//cd
void 			command_cd(/*int argc, */char **argv);
void			command_echo(char **argv);
void			command_pwd(void);
void			command_env(t_list *envs);
//export
//unset
void			command_unset(char **argv, t_list *envs, t_all all);
void			command_exit(char **argv);

int				pipe_found(char *line);
int				redirect_found(char *line);
int				dollar_found(char *line);
int				quote_found(char *line);

char			*get_env_value(char *key, t_list *envs);
int				is_this_key_env(char *key, t_list *envs);

void			free_double_array(char **array);
int				error_no_cmd(char *cmd);
int				error_no_file_dir(char *cmd);


#endif
