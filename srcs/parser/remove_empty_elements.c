/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_empty_elements.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwindom <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 04:43:25 by cwindom           #+#    #+#             */
/*   Updated: 2020/11/09 04:43:27 by cwindom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

static void	second_func(t_list_lexema *current, t_list_lexema *prev)
{
	char			*tmp_string;
	t_list_lexema	*tmp;

	if ((current->next->lexema->has_space_before) && \
		(current->next->lexema->string[0] != '\0'))
	{
		tmp_string = current->next->lexema->string;
		current->next->lexema->string = ft_strjoin(" ", \
										current->next->lexema->string);
		free(tmp_string);
	}
	else if (!(current->lexema->has_space_before) && prev)
	{
		tmp_string = prev->lexema->string;
		prev->lexema->string = ft_strjoin(prev->lexema->string, \
								current->next->lexema->string);
		free(tmp_string);
		tmp = current->next;
		current->next = current->next->next;
		free(tmp->lexema->string);
		free(tmp->lexema);
		free(tmp);
	}
}

static void	third_func(t_list_lexema **current, t_list_lexema *prev, \
						t_list_lexema **lexema_chain)
{
	t_list_lexema	*tmp;

	if ((*current)->lexema->lexema_type == lexema_type_simple_word)
	{
		if (prev == NULL)
			*lexema_chain = (*current)->next;
	}
	else
	{
		if ((*current)->next)
			second_func(*current, prev);
	}
	tmp = *current;
	*current = (*current)->next;
	if (prev)
	{
		prev->next = *current;
		*current = prev;
	}
	free(tmp->lexema->string);
	free(tmp->lexema);
	free(tmp);
	tmp = NULL;
}

void		remove_empty_elements(t_list_lexema **lexema_chain)
{
	t_list_lexema	*prev;
	t_list_lexema	*current;

	prev = NULL;
	current = *lexema_chain;
	while (current)
	{
		if (current->lexema->string[0] == '\0')
		{
			third_func(&current, prev, lexema_chain);
			continue;
		}
		prev = current;
		current = current->next;
	}
}
