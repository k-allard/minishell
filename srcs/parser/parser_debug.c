/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 02:53:08 by cwindom           #+#    #+#             */
/*   Updated: 2020/11/11 10:46:25 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parser_debug_print_lexema_list(t_list_lexema *lexema_list)
{
	t_lexema	*lexema;
	char		*i_string;

	while (lexema_list)
	{
		lexema = lexema_list->lexema;
		i_string = ft_itoa(lexema->lexema_type);
		ft_putstr_fd(i_string, STDERR_FILENO);
		free(i_string);
		ft_putstr_fd("\t-\t«", STDERR_FILENO);
		if (lexema->has_space_before)
			ft_putstr_fd("space+", STDERR_FILENO);
		else
			ft_putstr_fd("space-", STDERR_FILENO);
		ft_putstr_fd("\t-\t«", STDERR_FILENO);
		ft_putstr_fd(lexema->string, STDERR_FILENO);
		ft_putstr_fd("»\n", STDERR_FILENO);
		lexema_list = lexema_list->next;
	}
}

void	parser_debug_print_envs_list(t_list_env *envs_list)
{
	while (envs_list)
	{
		ft_putstr_fd(envs_list->env->key, STDERR_FILENO);
		ft_putstr_fd("\t-\t«", STDERR_FILENO);
		ft_putstr_fd(envs_list->env->value, STDERR_FILENO);
		ft_putstr_fd("»\n", STDERR_FILENO);
		envs_list = envs_list->next;
	}
}
