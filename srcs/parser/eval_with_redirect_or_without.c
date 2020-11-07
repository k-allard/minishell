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


static int apply_redirects(t_list_lexema *redirect)
{
	ft_putendl_fd("Redirect is not implemented", STDERR_FILENO);
	return (1);
}


static int is_redirect(t_lexema *lexema)
{
	int is_rdr;
	t_lexema_type t;

	t = lexema->lexemaType;
	is_rdr = (t == lexema_type_redirect_from);
	is_rdr = (t == lexema_type_redirect_to) || is_rdr;
	is_rdr = (t == lexema_type_redirect_to_append) || is_rdr;

	return (is_rdr);
}

static void split_command_with_redirect(t_list_lexema *all, t_list_lexema **cmd, t_list_lexema **redirect)
{
	t_list_lexema *prev;
	t_list_lexema *current;
	int is_find;

	prev = NULL;
	current = all;
	is_find = 0;
	while (current && !is_find)
	{
		if(is_redirect(current->lexema))
		{
			is_find = 1;
			if(prev == NULL)
				*cmd = NULL;
			else
			{
				prev->next = NULL;
				*cmd = all;
			}
			*redirect = current;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}


static int is_redirect_exist(t_list_lexema *lexemas)
{
	int is_find;

	is_find = 0;
	while (lexemas && !is_find)
	{
		is_find = is_redirect(lexemas->lexema);
		lexemas = lexemas->next;
	}
	return (is_find);
}

static int eval_without_redirect(t_list_lexema *command_lexemas, t_list_env *envs)
{
	int	res;

	res = eval_with_fork_or_without(command_lexemas, envs);
	return res;
}

static int eval_with_redirect(t_list_lexema *one_command_lexemas, t_list_env *envs)
{
	int res;
	t_list_lexema *redirect_only;
	t_list_lexema *command_only;

	res = 0;
	split_command_with_redirect(one_command_lexemas, &command_only, &redirect_only);
	res = apply_redirects(redirect_only);
	if(command_only != NULL && res == 0)
		res = eval_with_fork_or_without(command_only, envs);
	return res;
}

int eval_with_redirect_or_without(t_list_lexema *one_command_lexemas, t_list_env *envs)
{
	int res;

	res = 0;
	if(is_redirect_exist(one_command_lexemas))
		res = eval_with_redirect(one_command_lexemas, envs);
	else
		res = eval_without_redirect(one_command_lexemas, envs);
	return res;
}
