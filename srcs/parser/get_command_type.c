/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwindom <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 03:21:31 by cwindom           #+#    #+#             */
/*   Updated: 2020/11/09 03:21:35 by cwindom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

t_command	get_command_type(char *command_name)
{
	t_command	i;
	int			len;
	char		*commands[8];
	t_command	res;

	commands[COMMAND_CD] = "cd";
	commands[COMMAND_ECHO] = "echo";
	commands[COMMAND_EXPORT] = "export";
	commands[COMMAND_EXIT] = "exit";
	commands[COMMAND_ENV] = "env";
	commands[COMMAND_PWD] = "pwd";
	commands[COMMAND_UNSET] = "unset";
	len = ft_strlen(command_name) + 1;
	i = COMMAND_EXTERNAL;
	res = COMMAND_EXTERNAL;
	while (++i < NONE_COMMAND && res == COMMAND_EXTERNAL)
		if (ft_strncmp(command_name, commands[i], len) == 0)
			res = i;
	return (res);
}
