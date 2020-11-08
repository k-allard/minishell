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

int command_cd(char **argv, t_list *envs)
{
	DIR		*dir;
	char	*path;
	char	*pwd;
	char	*is_cwd;
    int		res;

	res = 0;
	path = (count_argv(argv) > 1) ? argv[1] : get_env_value("HOME", envs);
	if (path == NULL)
		return (17);
	pwd = get_env_value("PWD", (t_list *)envs);
	is_cwd = getcwd(0, 1024);
	if (!is_cwd && path[0] == '.' && path[1] == '\0')
	{
		update_env_data(envs, "OLDPWD", pwd);
		pwd = ft_strjoin(pwd, "/.");
		update_env_data(envs, "PWD", pwd);
		free(pwd);
	}
	else if(path[0] == '.' && path[1] == '\0')
	{
		update_env_data(envs, "OLDPWD", pwd);
		update_env_data(envs, "PWD", pwd);
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
				update_env_data(envs, "OLDPWD", pwd);
				pwd = getcwd(0, 1024);
				update_env_data(envs, "PWD", pwd);
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
