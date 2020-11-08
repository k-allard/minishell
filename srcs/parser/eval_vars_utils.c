/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_vars_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 15:26:49 by kallard           #+#    #+#             */
/*   Updated: 2020/11/08 16:45:44 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

void	eval_var(char **str_eval, char **str_original, t_list_env *envs)
{
	char	*var_name;

	var_name = get_var_name(*str_original);
	str_join_str(str_eval, get_env_value(var_name, (t_list *)envs));
	(*str_original) += (ft_strlen(var_name) + 1);
	free(var_name);
}

void	eval_param(char **str_eval, char **str_original, int argc, char **argv)
{
	int	param_index;

	param_index = (*((*str_original) + 1)) - '0';
	if (param_index < argc)
		str_join_str(str_eval, argv[param_index]);
	(*str_original) += 2;
}

void	eval_last_exit_value(char **str_eval, char **str_original)
{
	char	*exit_value;

	exit_value = ft_itoa(g_exit_value);
	str_join_str(str_eval, exit_value);
	(*str_original) += (ft_strlen(exit_value) + 1);
	free(exit_value);
}

void	eval_tilda(char **str_eval, char **str_original, t_list_env *envs)
{
	char	*home_dir;

	home_dir = get_env_value("HOME", (t_list *)envs);
	str_join_str(str_eval, home_dir);
	(*str_original) += 2;
}
