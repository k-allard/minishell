# include "../minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../t_lexema/t_lexema.h"
#include "../t_stream/t_stream.h"
#include "../t_command/t_command.h"
#include "parser.h"

static char** lexema_chain_2_argv(t_list_lexema *lexema_chain)
{
	char** args;
	int i;

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
	return args;
}

static char** list_env_2_env(t_list_env *env_list)
{
	char** env;
	int i;
	char *tmp;

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
	return env;
}

static int exec_external_command(t_list_lexema *lexema_chain, t_list_env *envs)
{
	char *command_name;
	char **args;
	char **env;
	int res;


	command_name = find_path(lexema_chain->lexema->string, (t_list *)envs);
	if (!command_name)
	{
		error_no_cmd(command_name);
		exit(-1) ;
	}
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
	free(command_name);
	free(args);
	return (res);
}



E_COMMAND get_command_type(char *command_name)
{
	E_COMMAND i;
	int len;
	char *commands[8];
	E_COMMAND res;

	commands[COMMAND_CD] = "cd";
	commands[COMMAND_ECHO] = "echo";
	commands[COMMAND_EXPORT] = "export";
	commands[COMMAND_EXIT] = "exit";
	commands[COMMAND_ENV] = "env";
	commands[COMMAND_PWD] = "pwd";
	commands[COMMAND_UNSET] = "unset";

	len = ft_strlen(command_name) + 1;
	i = COMMAND_EXTERNAL;
	res = COMMAND_EXTERNAL;
	while (++i < NONE_COMMAND && res == COMMAND_EXTERNAL)
		if (ft_strncmp(command_name, commands[i], len) == 0)
			res = i;
	return (res);
}

static int exec_builtin_command(E_COMMAND commandIndex, t_list_lexema *lexema_chain, t_list_env *envs)
{
	char **args;
	int res;

	args = lexema_chain_2_argv(lexema_chain);
	if (commandIndex == COMMAND_CD)
		res = command_cd(args, (t_list *)envs);
	else if(commandIndex == COMMAND_ECHO)
		res = command_echo(args);
	else if(commandIndex == COMMAND_EXPORT)
		res = command_export(args, (t_list *)envs);
	else if(commandIndex == COMMAND_EXIT)
		res = command_exit(args);
	else if(commandIndex == COMMAND_ENV)
		res = command_env((t_list *)envs);
	else if(commandIndex == COMMAND_PWD)
		res = command_pwd(envs);
	else if(commandIndex == COMMAND_UNSET)
		res = command_unset(args, (t_list *)envs);
	return (res);
}

int exec_external_or_builtin_command(t_list_lexema *lexema_chain, t_list_env *envs)
{
	E_COMMAND commandIndex;

	commandIndex = get_command_type(lexema_chain->lexema->string);
	if (commandIndex == COMMAND_EXTERNAL)
		return exec_external_command(lexema_chain, envs);
	else
		return exec_builtin_command(commandIndex, lexema_chain, envs);
}