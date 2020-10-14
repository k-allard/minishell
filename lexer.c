/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 00:11:40 by kallard           #+#    #+#             */
/*   Updated: 2020/10/15 00:12:16 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void init_lexer(t_lexer *lex, char *input, t_list *env_list)
{
    //...
	lex->input = input;
	lex->env_list = env_list;
}
