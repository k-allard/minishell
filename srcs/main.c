/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 22:38:46 by kallard           #+#    #+#             */
/*   Updated: 2020/10/24 23:41:26 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int		main(int argc, char **argv, char **envp)
{
	int		i;
	t_list	*envs;
	char	*line;
	char	**comands;

	g_envp = envp;
	envs = get_envs(argc, argv, envp);
	if(argc == 3 && ft_strncmp(argv[1], "-c", 3) == 0)
	{
		if ((comands = get_comands(argv[2])))
		{
			i = -1;
			while (comands[++i])
			{
				execute_commands(comands[i], envs);
				free(comands[i]);
			}
			free(comands);		
		}
	}
	else {
	line = NULL;
	while (1)
	{
		write_prompt();
		if (!deal_with_input(&line))
			continue ;
		if (!(comands = get_comands(line)))
			continue ;
		i = -1;
		while (comands[++i])
		{
			execute_commands(comands[i], envs);
			free(comands[i]);
		}
		free(comands);
	}
	}
	return (0);
}