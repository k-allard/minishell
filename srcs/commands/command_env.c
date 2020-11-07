/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:57:33 by kallard           #+#    #+#             */
/*   Updated: 2020/10/31 15:38:26 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	command_env(t_list *envs)
{
	if (!envs)
		return (17);
	ft_putstr_fd(((t_env *)envs->content)->key, 1);
	ft_putchar_fd('=', 1);
	ft_putendl_fd(((t_env *)envs->content)->value, 1);
	command_env(envs->next);
	return (0);
}
