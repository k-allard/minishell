/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 13:45:18 by kallard           #+#    #+#             */
/*   Updated: 2020/11/08 16:46:06 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_marker(t_lexema *lexema)
{
	if (lexema == NULL)
		return (0);
	if (lexema->lexema_type == lexema_type_redirect_from ||
	lexema->lexema_type == lexema_type_redirect_to_append ||
	lexema->lexema_type == lexema_type_redirect_to ||
	lexema->lexema_type == lexema_type_semicolon ||
	lexema->lexema_type == lexema_type_pipe)
		return (1);
	else
		return (0);
}

int			is_block(t_lexema *lexema)
{
	if (lexema == NULL)
		return (0);
	if (lexema->lexema_type == lexema_type_simple_word ||
		lexema->lexema_type == lexema_type_single_q ||
		lexema->lexema_type == lexema_type_double_q)
		return (1);
	else
		return (0);
}

static int	is_sequence_correct(t_lexema *lexema_prev, t_lexema *lexema)
{
	if (lexema_prev == NULL)
		return (is_block(lexema) || is_redirect(lexema));
	else
	{
		if (is_marker(lexema_prev) && is_marker(lexema))
		{
			if ((lexema_prev->string[0] == ';' || \
				lexema_prev->string[0] == '|') && \
				(lexema->string[0] == '>' || lexema->string[0] == '<'))
				return (1);
			else
				return (0);
		}
		else
			return (1);
	}
}

int			check_marker_syntaxis(t_list_lexema *lexema_list)
{
	t_lexema	*lexema_prev;
	t_lexema	*lexema;
	int			is_correct;

	is_correct = 1;
	lexema_prev = NULL;
	while (lexema_list && is_correct)
	{
		lexema = lexema_list->lexema;
		if ((is_correct = is_sequence_correct(lexema_prev, lexema)))
		{
			lexema_prev = lexema;
			lexema_list = lexema_list->next;
		}
	}
	is_correct = (is_correct && !is_marker(lexema));
	if (!is_correct)
	{
		ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
		ft_putstr_fd(lexema->string, STDERR_FILENO);
		ft_putendl_fd("\'", STDERR_FILENO);
		return (258);
	}
	return (0);
}
