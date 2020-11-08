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

#include "../minishell.h"

static int	cd_path(char *path, char *pwd, t_list *envs)
{
	DIR	*dir;
	int	res;

	res = 0;
	dir = opendir(path);
	if (dir != NULL)
	{
		if ((chdir(path) < 0) || (closedir(dir) < 0))
			res = 1;
		if (res == 0)
		{
			update_env_data(envs, "OLDPWD", pwd);
			pwd = getcwd(0, 1024);
			update_env_data(envs, "PWD", pwd);
			free(pwd);
		}
	}
	else
		res = 1;
	return (res);
}

static void	cd_point(char *pwd, t_list *envs)
{
	char	*is_cwd;

	is_cwd = getcwd(0, 1024);
	if (!is_cwd)
	{
		update_env_data(envs, "OLDPWD", pwd);
		pwd = ft_strjoin(pwd, "/.");
		update_env_data(envs, "PWD", pwd);
		free(pwd);
	}
	else
	{
		update_env_data(envs, "OLDPWD", pwd);
		update_env_data(envs, "PWD", pwd);
		free(is_cwd);
	}
}

int			command_cd(char **argv, t_list *envs)
{
	char	*path;
	char	*pwd;
	int		res;

	res = 0;
	path = (count_argv(argv) > 1) ? argv[1] : get_env_value("HOME", envs);
	if (path == NULL)
		return (17);
	pwd = get_env_value("PWD", (t_list *)envs);
	if (path[0] == '.' && path[1] == '\0')
		cd_point(pwd, envs);
	else
		res = cd_path(path, pwd, envs);
	if (res == 1)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	}
	return (res);
}
