/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_or_builtin_command.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 03:15:14 by cwindom           #+#    #+#             */
/*   Updated: 2020/11/10 19:55:28 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

char		**lexema_chain_2_argv(t_list_lexema *lexema_chain)
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

char		**list_env_2_env(t_list_env *env_list)
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
	int		res;

	command_name = find_path(lexema_chain->lexema->string, (t_list *)envs);
	if (!command_name)
	{
		ft_putstr_fd(lexema_chain->lexema->string, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		res = 127;
	}
	else
		res = external_command_exist(command_name, lexema_chain, envs);
	free(command_name);
	return (res);
}

static int	exec_builtin_command(t_command command_index,\
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
	free(args);
	return (res);
}

int			exec_external_or_builtin_command(t_list_lexema *lexema_chain,\
			t_list_env *envs)
{
	t_command command_index;

	command_index = get_command_type(lexema_chain->lexema->string);
	if (command_index == COMMAND_EXTERNAL)
		return (exec_external_command(lexema_chain, envs));
	else
		return (exec_builtin_command(command_index, lexema_chain, envs));
}
