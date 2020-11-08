/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lexema_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 01:56:05 by kallard           #+#    #+#             */
/*   Updated: 2020/11/09 02:14:01 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

int		is_blank(char symbol)
{
	if (symbol == ' ' || symbol == '\t')
		return (1);
	else
		return (0);
}

int		skip_blank(char **commandline)
{
	int has_space_before;

	has_space_before = 0;
	while (is_blank(**commandline))
	{
		has_space_before = 1;
		(*commandline)++;
	}
	return (has_space_before);
}

void	read_simple_symbol(char **commandline, t_lexema *lexema)
{
	char *symbol;
	char *tmp_string;

	symbol = ft_strnew(2);
	tmp_string = lexema->string;
	symbol[0] = *((*commandline)++);
	symbol[1] = '\0';
	lexema->string = ft_strjoin(tmp_string, symbol);
	free(tmp_string);
	free(symbol);
}

int		read_escape(char **commandline, t_lexema *lexema, int is_var_support)
{
	char *symbol;
	char *tmp_string;
	char tmp_symbol;

	(*commandline)++;
	tmp_symbol = *((*commandline)++);
	if (!tmp_symbol)
		return (0);
	symbol = ft_strnew(2);
	tmp_string = lexema->string;
	if (is_var_support && tmp_symbol == '$')
	{
		symbol[0] = '\\';
		symbol[1] = tmp_symbol;
	}
	else
		symbol[0] = tmp_symbol;
	lexema->string = ft_strjoin(tmp_string, symbol);
	free(tmp_string);
	free(symbol);
	return (0);
}

int		error_end_of_line(char quote_char)
{
	ft_putstr_fd("unexpected EOF while looking for matching `", STDERR_FILENO);
	ft_putchar_fd(quote_char, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	ft_putstr_fd("syntax error: unexpected end of file\n", STDERR_FILENO);
	return (2);
}
