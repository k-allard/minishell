/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:57:33 by kallard           #+#    #+#             */
/*   Updated: 2020/10/18 20:27:29 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		print_envs(t_list *envs)
{
	if (!envs)
		return ;
	ft_putstr_fd(((t_env *)envs->content)->name, 1);
	ft_putchar_fd('=', 1);
	ft_putendl_fd(((t_env *)envs->content)->value, 1);
	print_envs(envs->next);
}
