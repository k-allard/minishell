/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 22:38:46 by kallard           #+#    #+#             */
/*   Updated: 2020/11/11 11:12:39 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser/parser.h"

static void	update_shlvl(t_list_env *envs)
{
	char	*shlvl_str;
	int		shlvl;

	shlvl_str = get_env_value("SHLVL", envs);
	if (shlvl_str[0] == '\0')
	{
		shlvl_str = "1";
		update_env_data(envs, "SHLVL", shlvl_str);
		return ;
	}
	shlvl = ft_atoi(shlvl_str);
	shlvl++;
	shlvl_str = ft_itoa(shlvl);
	update_env_data(envs, "SHLVL", shlvl_str);
	free(shlvl_str);
}

int			main(int argc, char **argv, char **envp)
{
	t_args_struct	args_struct;
	char			*line;
	int				res;

	args_struct.argc = argc;
	args_struct.argv = argv;
	args_struct.envs = (t_list_env *)get_envs(envp);
	update_shlvl(args_struct.envs);
	signals();
	if (argc == 3 && ft_strncmp(argv[1], "-c", 3) == 0)
		res = parser(argv[2], &args_struct);
	else
	{
		line = NULL;
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
