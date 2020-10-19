/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 12:51:25 by kallard           #+#    #+#             */
/*   Updated: 2020/10/19 17:31:15 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char	**get_argv(char *line, t_list *envs)
{
	int		i;
	char	**argv;

	if (!(argv = ft_split(line, ' ')))
		return (0);
	//отдельно обработать случаи кавычек и переменных?
	return (argv);
}

int				exec_builtins(char *line, t_list *envs)
{
	char **argv;

	argv = get_argv(line, envs);
	if (!ft_strncmp(argv[0], "pwd", ft_strlen(argv[0])))
		command_pwd();
	else if (!ft_strncmp(argv[0], "echo", ft_strlen(argv[0])))
		command_echo(argv);
	// else if (!ft_strncmp(argv[0], "cd", ft_strlen(argv[0])))
	// 	command_cd(argv, envs);
	// else if (!ft_strncmp(argv[0], "env", ft_strlen(argv[0])))
	// 	command_env(argv, envs);
	// else if (!ft_strncmp(argv[0], "export", ft_strlen(argv[0])))
	// 	command_export(argv, envs);
	// else if (!ft_strncmp(argv[0], "unset", ft_strlen(argv[0])))
	// 	command_unset(argv, envs);
	else if (!ft_strncmp(argv[0], "exit", ft_strlen(argv[0])))
		command_exit(argv);
	else
	{
		return (0);
	}
	return (1);
    //не забыть free argv
}