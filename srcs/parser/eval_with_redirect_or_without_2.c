/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_with_redirect_or_without_2.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwindom <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 04:21:09 by cwindom           #+#    #+#             */
/*   Updated: 2020/11/09 04:21:11 by cwindom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

static t_list_lexema	*error_unexpected_redirect(t_lexema *lexema, int *res)
{
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(lexema->string, STDERR_FILENO);
	ft_putstr_fd("\'", STDERR_FILENO);
	*res = 2;
	return (NULL);
}

int						is_redirect(t_lexema *lexema)
{
	int				is_rdr;
	t_lexema_type	t;

	t = lexema->lexema_type;
	is_rdr = (t == lexema_type_redirect_from);
	is_rdr = (t == lexema_type_redirect_to) || is_rdr;
	is_rdr = (t == lexema_type_redirect_to_append) || is_rdr;
	return (is_rdr);
}

int						is_redirect_exist(t_list_lexema *lexemas)
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

t_list_lexema			*get_next_redirect(t_list_lexema **redirect, int *res)
{
	t_list_lexema *head;

	*res = 0;
	while ((*redirect) && !is_redirect((*redirect)->lexema))
		*redirect = (*redirect)->next;
	if ((*redirect) && is_redirect((*redirect)->lexema))
	{
		if ((*redirect)->next)
		{
			if (!is_redirect((*redirect)->next->lexema))
			{
				head = *redirect;
				*redirect = head->next->next;
				head->next->next = NULL;
				return (head);
			}
			else
				return (error_unexpected_redirect((*redirect)->next->lexema, \
				res));
		}
		else
			return (error_unexpected_redirect((*redirect)->lexema, res));
	}
	return (NULL);
}
