/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 23:07:16 by cwindom           #+#    #+#             */
/*   Updated: 2020/10/22 00:16:18 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../minishell.h"

int	count_argv(char **argv)
{
	int i;
	i = 0;

	while (argv[i])
	{
		i++;
	}
	return (i);
}

void command_cd(char **argv, t_list *envs)
{
	DIR		*dir;
	char	*path;
    int		er;
	int		n;

	er = 0;
	n = count_argv(argv);
	path = (n > 1) ? argv[1] : get_env_value("HOME", envs);
	if (path == NULL)
		return ;
	dir = opendir(path);
	if (dir != NULL)
	{
		if (chdir(path) < 0)
			er = 1;
		if (closedir(dir) < 0)
			er = 1;
	}
	else
		er = 1;
	if (er)
        printf("cd: %s: No such file or directory\n", argv[1]);
}
