/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 13:52:17 by kallard           #+#    #+#             */
/*   Updated: 2020/10/21 20:09:31 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int			is_this_key_env(char *key, t_list *envs)
{
	int		len;
	int		len_key_to_find;
	int		len_key_in_env;

	len_key_to_find = ft_strlen(key);
	len_key_in_env = ft_strlen((char *)((t_env *)envs->content)->key);
	len = (len_key_to_find > len_key_in_env) ? len_key_to_find : len_key_in_env;
	if (!(ft_strncmp(key, ((t_env *)envs->content)->key, len)))
		return (1);
	return (0);
}

char		*get_env_value(char *key, t_list *envs)
{
	while (envs)
	{
		if (is_this_key_env(key, envs))
			return (((t_env *)envs->content)->value);
		envs = envs->next;
	}
	return ("");
}