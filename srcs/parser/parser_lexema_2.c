/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lexema_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 01:55:52 by kallard           #+#    #+#             */
/*   Updated: 2020/11/09 02:14:01 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

int	malloc_error(char *commandline)
{
	ft_putstr_fd("memory allocation error during command line processing: ",
				STDERR_FILENO);
	ft_putendl_fd(commandline, STDERR_FILENO);
	return (5);
}

int	read_quote_param(char **commandline, t_lexema *lexema, char quote_char)
{
	(*commandline)++;
	while (lexema->string && **commandline && **commandline != quote_char)
	{
		if (**commandline == '\\')
		{
			if (quote_char == '"')
				read_escape(commandline, lexema, 1);
			else
				read_simple_symbol(commandline, lexema);
		}
		else
			read_simple_symbol(commandline, lexema);
	}
	if (lexema->string == NULL)
		return (malloc_error(*commandline));
	else if (**commandline == '\0')
		return (error_end_of_line(quote_char));
	else
		(*commandline)++;
	lexema->lexema_type = (quote_char == '"') ? \
		lexema_type_double_q : lexema_type_single_q;
	return (0);
}

int	read_pipe(char **commandline, t_lexema *lexema)
{
	read_simple_symbol(commandline, lexema);
	if (lexema->string == NULL)
		return (malloc_error(*commandline));
	lexema->lexema_type = lexema_type_pipe;
	return (0);
}

int	read_semicolon(char **commandline, t_lexema *lexema)
{
	read_simple_symbol(commandline, lexema);
	if (lexema->string == NULL)
		return (malloc_error(*commandline));
	lexema->lexema_type = lexema_type_semicolon;
	return (0);
}

int	read_redirect_to(char **commandline, t_lexema *lexema)
{
	int i;

	i = 0;
	while (lexema->string && **commandline && **commandline == '>' && i++ < 2)
	{
		read_simple_symbol(commandline, lexema);
	}
	if (lexema->string == NULL)
		return (malloc_error(*commandline));
	lexema->lexema_type = (i == 1) ? lexema_type_redirect_to : \
		lexema_type_redirect_to_append;
	return (0);
}
