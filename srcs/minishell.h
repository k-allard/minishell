/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 22:38:29 by kallard           #+#    #+#             */
/*   Updated: 2020/11/02 19:02:19 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>					//	этот инклюд нужен, но не забыть потом заменить все оригинальные принтэфы на ft_ (если будут)

#include <dirent.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

#include "t_lexema/t_lexema.h"



/*
** Глабальные переменные
*/
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

typedef	struct		s_list_env
{
    t_env			*env;
    struct s_list_env	*next;
}					t_list_env;

typedef	struct		s_list_lexema
{
    t_lexema			*lexema;
    struct s_list_lexema	*next;
}					t_list_lexema;

typedef struct	s_pipe
{
	char		*left_end;
	char		**argv;
}				t_pipe;

enum			e_quotes
{
	SING_Q = 0,
	DUBL_Q,
	ETC
};

typedef struct	s_quotes
{
	int			type;
	int			start;
	int			end;
}				t_quotes;

t_list			*get_envs(int argc, char **argv, char **envp);
void			write_prompt();

int				deal_with_input(char **line);
char			**get_comands(char *line);
char		    *find_path(char *argv, t_list *envs);
char			**get_argumentes(char *line, t_list *envs);
char			*deal_with_quotes(char *argv, t_list *envs);
char			 *insert_variable(char *argv, t_list *envs);
int				print_exit_status(char *line);
void			execute_commands(char *line, t_list *envs);

void			execute_pipes(char *line, t_list *envs);
void			execute_others(char *line, t_list *envs);
int				execute_builtins(char *line, t_list *envs);
int 			command_cd(char **argv, t_list *envs);
int				command_echo(char **argv);
int				command_pwd(t_list_env *envs);
int				command_env(t_list *envs);
int           	command_export(char **argv, t_list *envs);
int				command_unset(char **argv, t_list *envs);
int				command_exit(char **argv, int i);

int		pipe_found(char *line);
int		redirect_found(char *line);
int		dollar_found(char *line);
int		quote_found(char *line);

char		*get_env_value(char *key, t_list *envs);
int			is_this_key_env(char *key, t_list *envs);
int is_redirect(t_lexema *lexema);

int update_env_data(t_list *envs, char *new_env, char *new_data);


void	free_double_array(char **array);
int		error_no_cmd(char *cmd);
int		error_no_file_dir(char *cmd);
int	valid_name_first(int ch);
int	valid_name(char *str);
void signals();
int	count_argv(char **argv);


#endif
