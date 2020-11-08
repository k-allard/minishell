/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 22:38:46 by kallard           #+#    #+#             */
/*   Updated: 2020/11/08 16:45:26 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "parser/parser.h"

int		main(int argc, char **argv, char **envp)
{
	int			i;
	t_list_env	*envs;
	char		*line;
	char		**comands;
	int			res;

	g_envp = envp;
	envs = (t_list_env *)get_envs(envp);
	signals();
	if (argc == 3 && ft_strncmp(argv[1], "-c", 3) == 0)
		res = parser(argv[2], argc, argv, envs);
	else
	{
		line = NULL;
		while (1)
		{
			write_prompt();
			if (!deal_with_input(&line))
				continue;
			res = parser(line, argc, argv, envs);
			free(line);
		}
	}
	free_envs_list(envs);
	return (res);
}
