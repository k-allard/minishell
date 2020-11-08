# include "../minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../t_lexema/t_lexema.h"
#include "../t_stream/t_stream.h"
#include "../t_command/t_redirects_close.h"
#include "parser.h"

static t_list_lexema* error_unexpected_redirect(t_lexema *lexema, int *res)
{
    ft_putstr_fd("bash: синтаксическая ошибка рядом с неожиданным маркером «", STDERR_FILENO);
    ft_putstr_fd(lexema->string, STDERR_FILENO);
    ft_putstr_fd("bash: синтаксическая ошибка рядом с неожиданным маркером «", STDERR_FILENO);

    *res = 2;
    return NULL;
}

int is_redirect(t_lexema *lexema)
{
    int is_rdr;
    t_lexema_type t;

    t = lexema->lexema_type;
    is_rdr = (t == lexema_type_redirect_from);
    is_rdr = (t == lexema_type_redirect_to) || is_rdr;
    is_rdr = (t == lexema_type_redirect_to_append) || is_rdr;

    return (is_rdr);
}

static t_list_lexema* get_next_redirect(t_list_lexema **redirect, int *res)
{
    t_list_lexema* head;

    *res = 0;
    while((*redirect) && !is_redirect((*redirect)->lexema))
        *redirect = (*redirect)->next;
    if((*redirect) && is_redirect((*redirect)->lexema))
    {
        if((*redirect)->next)
        {
            if(!is_redirect((*redirect)->next->lexema))
            {
                head = *redirect;
                *redirect = head->next->next;
                head->next->next = NULL;
                return head;
            }
            else
                return error_unexpected_redirect((*redirect)->next->lexema, res);
        }
        else
            return error_unexpected_redirect((*redirect)->lexema, res);
    }
    return NULL;
}

static int close_current_fd(int *current_fd)
{
    int res;

    if(*current_fd != -1)
    {
        res = close(*current_fd);
        if(res == -1)
            ft_putendl_fd(strerror(errno), STDERR_FILENO);
        return res;
    }
    else
    {
        *current_fd = -1;
        return (0);
    }
}

static int open_redirect_fd(int* current_fd, int std_fd, char *filename, int flags)
{
    int res;

    if((res = close(std_fd)) == 0)
    {
        *current_fd = open(filename, flags, 0644);
        if(*current_fd == -1)
        {
            ft_putstr_fd("Error by start redirect with file: ", STDERR_FILENO);
            ft_putendl_fd(filename, STDERR_FILENO);
            res = -1;
        }
    }
    return res;
}

static int set_redirect_stdout(t_redirects *redirects_fd, char *filename, int flags)
{
    int res;

    if(redirects_fd->stdout_fd == -1)
        redirects_fd->stdout_original = dup(STDOUT_FILENO);
    res = -1;
    if((res = open_redirect_fd(&(redirects_fd->stdout_fd), STDOUT_FILENO, filename, flags)) == 0)
        if((res = dup2(redirects_fd->stdout_fd, STDOUT_FILENO)) != -1)
            res = 0;
    if(res != 0)
        ft_putendl_fd(strerror(errno), STDERR_FILENO);
    return res;
}

static int set_redirect_stdin(t_redirects *redirects_fd, char *filename, int flags)
{
    int res;

    if(redirects_fd->stdin_fd == -1)
        redirects_fd->stdin_original = dup(STDIN_FILENO);
    res = -1;
    if(0 == open_redirect_fd(&(redirects_fd->stdin_fd), STDIN_FILENO, filename, flags))
        if(-1 != dup2(redirects_fd->stdin_fd, STDIN_FILENO))
            res = 0;
    if(res != 0)
        ft_putendl_fd(strerror(errno), STDERR_FILENO);
    return res;
}

static int apply_redirects(t_list_lexema *redirect, t_redirects *redirects_fd)
{
    t_list_lexema *one_redirect;
    int res;

    while ((one_redirect = get_next_redirect(&redirect, &res)) && res == 0)
    {
        if(one_redirect->lexema->lexema_type == lexema_type_redirect_to)
        {
            res = set_redirect_stdout(redirects_fd, one_redirect->next->lexema->string, \
            O_WRONLY | O_CREAT | O_TRUNC);
        }
        else if (one_redirect->lexema->lexema_type == lexema_type_redirect_to_append)
        {
            res = set_redirect_stdout(redirects_fd, one_redirect->next->lexema->string, \
            O_WRONLY | O_CREAT | O_APPEND);
        }
        else if (one_redirect->lexema->lexema_type == lexema_type_redirect_from)
        {
            res = set_redirect_stdin(redirects_fd, one_redirect->next->lexema->string, \
            O_RDONLY);
        }
    }
	return (res);
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
    t_redirects redirects_fd;

	res = 0;
    redirects_fd.stdout_original = -1;
    redirects_fd.stdin_original = -1;
    redirects_fd.stdin_fd = -1;
    redirects_fd.stdout_fd = -1;
	split_command_with_redirect(one_command_lexemas, &command_only, &redirect_only);

    res = apply_redirects(redirect_only, &redirects_fd);
    if (command_only != NULL && res == 0)
        res = eval_with_fork_or_without(command_only, envs);
    if ( (t_redirects_close(&redirects_fd) == -1) && (res == 0))
        res = 1;
    return (res);
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
