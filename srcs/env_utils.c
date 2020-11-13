/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 13:52:17 by kallard           #+#    #+#             */
/*   Updated: 2020/11/11 11:33:17 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_this_key_env(char *key, t_list_env *envs)
{
	int		len;
	int		len_key_to_find;
	int		len_key_in_env;

	len_key_to_find = ft_strlen(key);
	len_key_in_env = ft_strlen(envs->env->key);
	len = (len_key_to_find > len_key_in_env) ? len_key_to_find : len_key_in_env;
	if (!(ft_strncmp(key, envs->env->key, len)))
		return (1);
	return (0);
}

char		*get_env_value(char *key, t_list_env *envs)
{
	while (envs)
	{
		if (is_this_key_env(key, envs))
			return (envs->env->value);
		envs = envs->next;
	}
	return ("");
}
