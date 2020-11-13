/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_vars_and_unescape_in_lexema_chain.c           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwindom <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 14:17:31 by cwindom           #+#    #+#             */
/*   Updated: 2020/11/09 14:17:34 by cwindom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

static void	unescape(char **str_eval, char **str_original)
{
	str_join_str(str_eval, "$");
	(*str_original) += 2;
}

static void	simple_join_symbol(char **str_eval, char **str_original)
{
	str_join_char(str_eval, **str_original);
	(*str_original)++;
}

static void	eval_vars_and_params(char **str_eval, char **str_original, \
			t_args_struct *args_struct)
{
	if (*((*str_original) + 1) == '?')
		eval_last_exit_value(str_eval, str_original);
	else if (is_var_name_symbol(*((*str_original) + 1)))
	{
		eval_var(str_eval, str_original, args_struct->envs);
	}
	else if (is_var_name_symbol_with_num(*((*str_original) + 1)))
		eval_param(str_eval, str_original, args_struct->argc, \
					args_struct->argv);
	else
		simple_join_symbol(str_eval, str_original);
}

static void	eval_vars_and_unescape(t_lexema *lexema, t_args_struct *args_struct)
{
	char *str_original;
	char *str_eval;

	str_eval = ft_strdup("");
	str_original = lexema->string;
	if (*str_original == '~' && *(str_original + 1) == '\0')
	{
		eval_tilda(&str_eval, &str_original, args_struct->envs);
	}
	else
		while (*str_original)
		{
			if (*str_original == '\\' && *(str_original + 1) == '$')
				unescape(&str_eval, &str_original);
			else if (*str_original == '$')
				eval_vars_and_params(&str_eval, &str_original, args_struct);
			else
				simple_join_symbol(&str_eval, &str_original);
		}
	free(lexema->string);
	lexema->string = str_eval;
}

void		eval_vars_unesc_dol_in_lex_chain(t_list_lexema *lexema_chain, \
			t_args_struct *args_struct)
{
	t_lexema *lexema;

	while (lexema_chain)
	{
		lexema = lexema_chain->lexema;
		if (lexema->lexema_type == lexema_type_simple_word ||
		lexema->lexema_type == lexema_type_double_q)
		{
			eval_vars_and_unescape(lexema, args_struct);
		}
		lexema_chain = lexema_chain->next;
	}
}
