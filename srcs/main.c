/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 22:38:46 by kallard           #+#    #+#             */
/*   Updated: 2020/11/09 17:09:04 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser/parser.h"

int		main(int argc, char **argv, char **envp)
{
	t_args_struct	args_struct;
	char			*line;
	int				res;

	args_struct.argc = argc;
	args_struct.argv = argv;
	args_struct.envs = (t_list_env *)get_envs(envp);
	signals();
	if (argc == 3 && ft_strncmp(argv[1], "-c", 3) == 0)
		res = parser(argv[2], &args_struct);
	else
	{
		line = ft_strdup("");
		while (1)
		{
			write_prompt();
			if (!deal_with_input(&line))
				continue;
			res = parser(line, &args_struct);
			free(line);
		}
	}
	free_envs_list(args_struct.envs);
	return (res);
}
