/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 16:23:13 by kallard           #+#    #+#             */
/*   Updated: 2020/10/31 15:39:30 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	command_pwd(t_list_env *envs)
{
	char	*pwd;

	//	pwd = getcwd(0, 1024);
	pwd = get_env_value("PWD", (t_list *)envs);
	ft_putendl_fd(pwd, 1);
//	free(pwd);
	return (0);
}