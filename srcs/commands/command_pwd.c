/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 16:23:13 by kallard           #+#    #+#             */
/*   Updated: 2020/11/11 11:15:23 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	command_pwd(t_list_env *envs)
{
	char	*pwd;

	pwd = get_env_value("PWD", (t_list_env *)envs);
	ft_putendl_fd(pwd, 1);
	return (0);
}
