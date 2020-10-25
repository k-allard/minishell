/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 23:07:16 by cwindom           #+#    #+#             */
/*   Updated: 2020/10/24 23:58:15 by kallard          ###   ########.fr       */
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
	DIR		*dir; //Тип, представляющий поток каталога
	char	*path;
    char    *pwd;
    int		er; //можно положить в структуру с ошибками
	int n;

	er = 0;
	n = count_argv(argv);
	// printf("n:%d", n);
	path = (n > 1) ? argv[1] : get_env_value("HOME", envs);
	if (path == NULL)
		return ;
	if(path[0] == '.' && path[1] == '\0')
	{
		pwd = getcwd(0, 1024);
		path = ft_strjoin(pwd, "/.");
		chdir(path);
		free(pwd);
		free(path);
	}
	else
	{
		dir = opendir(path);
		if (dir != NULL)
		{
			if ((chdir(path) < 0) || (closedir(dir) < 0))
				er = 1;
		}
		else
			er = 1;		
	}
	
	//if (er)
     //   printf("%s", "вывести ошибку с помощью strerror(errno)");
}
