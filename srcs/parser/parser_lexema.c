/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lexema.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 01:55:57 by kallard           #+#    #+#             */
/*   Updated: 2020/11/09 02:14:01 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

static int		read_redirect_from(char **commandline, t_lexema *lexema)
{
	int i;

	i = 1;
	while (lexema->string && **commandline && **commandline == '<' && i++ <= 1)
	{
		read_simple_symbol(commandline, lexema);
	}
	if (lexema->string == NULL)
		return (malloc_error(*commandline));
	lexema->lexema_type = lexema_type_redirect_from;
	return (0);
}

static int		is_simple_symbol(char symbol)
{
	char *non_simple_symbols;

	non_simple_symbols = "'\" \t<>|;";
	if (ft_strchr(non_simple_symbols, (int)symbol))
		return (0);
	else
		return (1);
}

static int		read_simple_word(char **commandline, t_lexema *lexema)
{
	while (lexema->string && **commandline && is_simple_symbol(**commandline))
	{
		if (**commandline == '\\')
			read_escape(commandline, lexema, 1);
		else
			read_simple_symbol(commandline, lexema);
	}
	if (lexema->string == NULL)
		return (malloc_error(*commandline));
	lexema->lexema_type = lexema_type_simple_word;
	return (0);
}

static t_lexema	*get_next_lexema(char **commandline, int *res)
{
	t_lexema	*lexema;
	int			has_space_before;

	*res = 0;
	has_space_before = skip_blank(commandline);
	if (**commandline == '\0')
		return (NULL);
	lexema = t_lexema_init();
	if (**commandline == '"')
		*res = read_quote_param(commandline, lexema, '"');
	else if (**commandline == '\'')
		*res = read_quote_param(commandline, lexema, '\'');
	else if (**commandline == '|')
		*res = read_pipe(commandline, lexema);
	else if (**commandline == ';')
		*res = read_semicolon(commandline, lexema);
	else if (**commandline == '>')
		*res = read_redirect_to(commandline, lexema);
	else if (**commandline == '<')
		*res = read_redirect_from(commandline, lexema);
	else
		*res = read_simple_word(commandline, lexema);
	lexema->has_space_before = has_space_before;
	return (lexema);
}

t_list_lexema	*get_lexema_list(char *commandline, int *res)
{
	t_lexema	*lexema;
	t_list		*lexema_list;

	lexema_list = NULL;
	while ((lexema = get_next_lexema(&commandline, res)) && (*res == 0))
		ft_lstadd_back(&lexema_list, ft_lstnew(lexema));
	return ((t_list_lexema *)lexema_list);
}
