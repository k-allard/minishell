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

static int is_pipe_in_lexema_chain(t_list_lexema *lexema_chain)
{
	int is_pipe = 0;
	while (lexema_chain && !is_pipe)
	{
		if(lexema_chain->lexema->lexemaType == lexema_type_pipe)
			is_pipe = 1;
		lexema_chain = lexema_chain->next;
	}
	return is_pipe;
}

static int eval_without_pipe(t_list_lexema *lexema_chain, t_list_env *envs)
{
	return (eval_with_redirect_or_without(lexema_chain, envs));
}

static int eval_with_pipe(t_list_lexema *lexema_chain, t_list_env *envs)
{
	t_list_lexema *one_command_lexemas;
	int		    file_pipes[2];
	pid_t		pid[2];
	int res[2];
	int status[2];

	one_command_lexemas = get_next_lexema_chain(&lexema_chain, lexema_type_pipe);

	if(pipe(file_pipes) < 0) {
		ft_putstr_fd("Pipe could not be initialized\n", STDERR_FILENO);
		exit(9);
	}
	pid[0] = fork();
	if (pid[0] < 0)
	{
		ft_putstr_fd("Could not fork\n", STDERR_FILENO);
		exit(10);
	}

	if (pid[0] == 0) {
		close(file_pipes[0]);
		dup2(file_pipes[1], STDOUT_FILENO);
		close(file_pipes[1]);

		if((res[0] = eval_without_pipe(one_command_lexemas, envs)) < 0)
		{
			ft_putstr_fd("Error: ошибка выполнения команды\n", STDERR_FILENO);
			parser_debug_print_lexema_list(one_command_lexemas);
		}
		exit(res[0]);
	}
	else
	{
		waitpid(pid[0], &(status[0]), 0);
		if (WIFEXITED(status[0]))
			res[0] = WEXITSTATUS(status[0]);
		close(file_pipes[1]);
		pid[1] = fork();
		if (pid[1] < 0)
		{
			ft_putstr_fd("Could not fork\n", STDERR_FILENO);
			exit(10);
		}
		if (pid[1] == 0) {
			close(file_pipes[1]);
			dup2(file_pipes[0], STDIN_FILENO);
			close(file_pipes[0]);

			if((res[1] = eval_with_pipe_or_without(lexema_chain, envs)) < 0)
			{
				ft_putstr_fd("Error: ошибка выполнения команды\n", STDERR_FILENO);
				parser_debug_print_lexema_list(lexema_chain);
			}
			exit(res[1]);
		}
		else
		{
			waitpid(pid[1], &(status[1]), 0);
			if (WIFEXITED(status[1]))
				res[1] = WEXITSTATUS(status[1]);
			else
				res[1] = -1;
			return (res[1]);
		}
	}
}

int eval_with_pipe_or_without(t_list_lexema *lexema_chain, t_list_env *envs)
{
	int res;
	if (is_pipe_in_lexema_chain(lexema_chain))
		res = eval_with_pipe(lexema_chain, envs);
	else
		res = eval_without_pipe(lexema_chain, envs);
	g_exit_value = res;
	return (res);
}