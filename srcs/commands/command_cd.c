/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 23:07:16 by cwindom           #+#    #+#             */
/*   Updated: 2020/10/31 15:31:46 by kallard          ###   ########.fr       */
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

int command_cd(char **argv, t_list *envs)
{
	DIR		*dir;
	char	*path;
	char	*pwd;
	char *is_cwd;
    int		res;
	int		n;

	res = 0;
	//if (argc > 1) //если после cd есть путь
//		path = argv[1];
	//else //если путь не указан
        //printf("%s", "Здесь будет какой-то код чтобы попасть в Home");

	n = count_argv(argv);
	path = (n > 1) ? argv[1] : get_env_value("HOME", envs);

	if (path == NULL)
		return 17;
	pwd = get_env_value("PWD", (t_list *)envs);
	is_cwd = getcwd(0, 1024);//TODO 1: получать PWD из переменных - getpwd(envs);
	if(!is_cwd && path[0] == '.' && path[1] == '\0')
	{
		update_env_data(envs, "OLDPWD", pwd); //обновляем OLDPWD в переменных
		pwd = ft_strjoin(pwd, "/.");
		update_env_data(envs, "PWD", pwd); //обновляем PWD в переменных
//		chdir(pwd); //TODO: сделать вместо chdir функцию chpwd, чтобы она ставила PWD env + OWDPWD env и выполняла chdir
		free(pwd);
//		free(path);
	}
	else if(path[0] == '.' && path[1] == '\0')
	{
		update_env_data(envs, "OLDPWD", pwd); //обновляем OLDPWD в переменных
//		pwd = ft_strjoin(pwd, "/.");
		update_env_data(envs, "PWD", pwd); //обновляем PWD в переменных
		chdir(pwd); //TODO: сделать вместо chdir функцию chpwd, чтобы она ставила PWD env + OWDPWD env и выполняла chdir
		free(pwd);
//		free(path);
	}
	else
	{
		dir = opendir(path);
		if (dir != NULL)
		{
			if ((chdir(path) < 0) || (closedir(dir) < 0))
				res = 1;
			if (res == 0)
			{
				update_env_data(envs, "OLDPWD", pwd); //обновляем OLDPWD в переменных
				pwd = getcwd(0, 1024);
				update_env_data(envs, "PWD", pwd); //обновляем PWD в переменных
			}
		}
		else
			res = 1;
	}
	if (res == 1)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	}
	return (res);
}
