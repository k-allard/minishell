/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 22:38:46 by kallard           #+#    #+#             */
/*   Updated: 2020/10/21 22:30:52 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

#include "t_lexema/t_lexema.h"
#include "t_stream/t_stream.h"
#include "t_command/t_command.h"
#include "parser/parser.h"


int		main(int argc, char **argv, char **envp)
{
	int		i;
	t_list	*envs;
	char	*line;
	char	**comands;

	g_envp = envp;
	envs = get_envs(argc, argv, envp);
//    parser("  echo 'he \\$test \\llo' \"1\\\"\\$a $USER    \" 1\\ 2\\$t 3\\ $PWD ; echo 1 | cat  ; echo 2 | cat | cat | cat | cat | cat > test.txt",
//           argc, argv, (t_list_env*)envs);
//    parser("  echo 'he \\$test \\llo' \"1\\\"\\$a $USER  $0  \" A\\ $1\\ A 1\\ 2\\$t 3\\ $PWD ; echo 1 | cat ",
           parser("echo tttttt ; pwd ; ping localhost -c 1 ; echo 2",
           argc, argv, (t_list_env*)envs);
    return 0;

	if(argc == 3 && ft_strncmp(argv[1], "-c", 3) == 0)
	{
        parser(argv[2], argc, argv, (t_list_env*)envs);
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