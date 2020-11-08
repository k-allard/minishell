/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 19:42:19 by kallard           #+#    #+#             */
/*   Updated: 2020/10/21 21:28:57 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double_array(char **array)
{
	int		i;

	if (!array)
		return ;
	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

int		error_no_cmd(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	return (127);
}

void	free_envs_list(t_list_env *envs)
{
	t_list_env *arch_elem;

	if (!envs)
		return ;
	while (envs)
	{
		free(envs->env->key);
		free(envs->env->value);
		free(envs->env);
		arch_elem = envs;
		envs = arch_elem->next;
		free((void *)arch_elem);
	}
}
