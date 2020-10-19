/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_comands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 12:51:25 by kallard           #+#    #+#             */
/*   Updated: 2020/10/19 12:53:00 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int				exec_builtins(char *line, t_list *envs)
{
	char **argv;

//получить аргументы!
	if (!ft_strncmp(argv[0], "cd", ft_strlen(argv[0])))
		cmd_cd(argv, envs);
	else if (!ft_strncmp(argv[0], "echo", ft_strlen(argv[0])))
		cmd_echo(argv);
	else if (!ft_strncmp(argv[0], "pwd", ft_strlen(argv[0])))
		cmd_pwd();
	else if (!ft_strncmp(argv[0], "env", ft_strlen(argv[0])))
		cmd_env(argv, envs);
	else if (!ft_strncmp(argv[0], "export", ft_strlen(argv[0])))
		cmd_export(argv, envs);
	else if (!ft_strncmp(argv[0], "unset", ft_strlen(argv[0])))
		cmd_unset(argv, envs);
	else if (!ft_strncmp(argv[0], "exit", ft_strlen(argv[0])))
		cmd_exit(argv);
	else
	{
		return (0);
	}
	return (1);
    //не забыть free argv
}