/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_or_builtin_command.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwindom <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 03:15:14 by cwindom           #+#    #+#             */
/*   Updated: 2020/11/09 03:15:17 by cwindom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "parser.h"

static char	**lexema_chain_2_argv(t_list_lexema *lexema_chain)
{
	char	**args;
	int		i;

	i = ft_lstsize((t_list *)lexema_chain);
	args = (char **)(malloc(sizeof(char *) * (i + 1)));
	i = 0;
	while (lexema_chain)
	{
		args[i] = lexema_chain->lexema->string;
		i++;
		lexema_chain = lexema_chain->next;
	}
	args[i] = NULL;
	return (args);
}

static char	**list_env_2_env(t_list_env *env_list)
{
	char	**env;
	int		i;
	char	*tmp;

	i = ft_lstsize((t_list *)env_list);
	env = (char **)(malloc(sizeof(char *) * (i + 1)));
	i = 0;
	while (env_list)
	{
		tmp = ft_strjoin("=", env_list->env->value);
		env[i] = ft_strjoin(env_list->env->key, tmp);
		free(tmp);
		i++;
		env_list = env_list->next;
	}
	env[i] = NULL;
	return (env);
}

static int	exec_external_command(t_list_lexema *lexema_chain, t_list_env *envs)
{
	char	*command_name;
	char	**args;
	char	**env;
	int		res;

	command_name = find_path(lexema_chain->lexema->string, (t_list *)envs);
	if (!command_name)
	{
		ft_putstr_fd(lexema_chain->lexema->string, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		res = 127;
	}
	else
	{
		args = lexema_chain_2_argv(lexema_chain);
		env = list_env_2_env(envs);
		if ((res = execve(command_name, args, env)) < 0)
		{
			if (errno == ENOENT)
			{
				ft_putstr_fd(command_name, STDERR_FILENO);
				ft_putendl_fd(": command not found", STDERR_FILENO);
				res = 127;
			}
			else
				res = errno;
		}
		free_double_array(args);
		free_double_array(env);
	}
	free(command_name);
	return (res);
}

static int	exec_builtin_command(E_COMMAND command_index,\
t_list_lexema *lexema_chain, t_list_env *envs)
{
	char	**args;
	int		res;

	res = 0;
	args = lexema_chain_2_argv(lexema_chain);
	if (command_index == COMMAND_CD)
		res = command_cd(args, (t_list *)envs);
	else if (command_index == COMMAND_ECHO)
		res = command_echo(args);
	else if (command_index == COMMAND_EXPORT)
		res = command_export(args, (t_list *)envs);
	else if (command_index == COMMAND_EXIT)
		res = command_exit(args);
	else if (command_index == COMMAND_ENV)
		res = command_env((t_list *)envs);
	else if (command_index == COMMAND_PWD)
		res = command_pwd(envs);
	else if (command_index == COMMAND_UNSET)
		res = command_unset(args, (t_list *)envs, 0);
	free_double_array(args);
	return (res);
}

int			exec_external_or_builtin_command(t_list_lexema *lexema_chain,\
t_list_env *envs)
{
	E_COMMAND command_index;

	command_index = get_command_type(lexema_chain->lexema->string);
	if (command_index == COMMAND_EXTERNAL)
		return (exec_external_command(lexema_chain, envs));
	else
		return (exec_builtin_command(command_index, lexema_chain, envs));
}
