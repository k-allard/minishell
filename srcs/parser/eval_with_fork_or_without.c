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



static int is_exit_command(t_lexema *lexema)
{
	char *exit_str;

	exit_str = "exit";
	if(ft_strncmp(lexema->string, exit_str, 5) == 0)
		return (1);
	else
		return (0);
}

int eval_without_fork(t_list_lexema *one_command_lexemas, t_list_env *envs)
{
	return (exec_external_or_builtin_command(one_command_lexemas, envs));
}

int eval_with_fork(t_list_lexema *one_command_lexemas, t_list_env *envs)
{
	int		    file_pipes[2];
	pid_t		pid;
	int res;
	int status;

	if (pipe(file_pipes) < 0) {
		ft_putstr_fd("Pipe could not be initialized\n", STDERR_FILENO);
		exit(9);
	}
	pid = fork();
	if (pid < 0) {
		ft_putstr_fd("Could not fork\n", STDERR_FILENO);
		exit(10);
	}

	if (pid == 0) {

		if ((res = eval_without_fork(one_command_lexemas, envs)) < 0)
		{
			ft_putstr_fd("Error: ошибка выполнения команды\n", STDERR_FILENO);
			parser_debug_print_lexema_list(one_command_lexemas);
		}
		exit(res);
	} else {
		waitpid(pid, &(status), 0);
		if (WIFEXITED(status))
			res = WEXITSTATUS(status);
		else
			res = -1;
		return (res);
	}
}

int eval_with_fork_or_without(t_list_lexema *cmd, t_list_env *envs)
{
	E_COMMAND commandIndex;

	commandIndex = get_command_type(cmd->lexema->string);

	if(commandIndex == COMMAND_EXTERNAL)
		return eval_with_fork(cmd, envs);
	else
		return eval_without_fork(cmd, envs);
}