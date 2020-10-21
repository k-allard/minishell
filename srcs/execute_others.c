/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_others.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 19:35:15 by kallard           #+#    #+#             */
/*   Updated: 2020/10/21 23:51:11 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"
# include <sys/stat.h>
# include <stdio.h>

char		*find_path(char *argv, t_list *envs)
{
	int			i;
	char		*tmp;
	char		*new_path;
	char		**paths;
	struct stat	s;

	if (!(tmp = get_env_value("PATH", envs)))
		return (NULL);
	paths = ft_split(tmp, ':');
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin("/", argv);
		new_path = ft_strjoin(paths[i], tmp);
		free(tmp);
		if (stat(new_path, &s) == 0)    // int stat(char *filename, struct stat *statbuf); 
        // вносит в структуру, на которую указывает statbuf, информацию, содержащуюся в файле, 
        // связанном с указателем filename. Структура stat определена в sys\stat.h. 
        // При успешном заполнении структуры stat возвращается 0. В случае неудачи возвращается —1
		{
			free_double_array(paths);
			return (new_path);
		}
		free(new_path);
	}
	free_double_array(paths);
	return (ft_strdup(argv));
}

void			execute_others(char *line, t_list *envs)
{
	int		status;
	char	*filename;
	char	**argv;
	pid_t	pid;

	argv = get_argumentes(line, envs);
	filename = find_path(argv[0], envs);
	if (!filename)
	{
		error_no_cmd(argv[0]);
		return ;
	}
    ft_putendl_fd("[We are in execute_others]", 1);
	pid = fork();
	if (pid == 0)
	{
        ft_putendl_fd("[This message is from child process]", 1);
		if (execve(filename, argv, g_envp) == -1)     // int execve(const char *filename, char *const argv[], char* const envp[]); 
        // , где filename - имя программы для исполнения
			exit(error_no_cmd(argv[0]));
		exit(EXIT_SUCCESS);
	}
	wait(&status);
    ft_putendl_fd("[Child process terminated]", 1);
	free(filename);
	free_double_array(argv);
    if (WIFEXITED(status))  // if the process terminated normally by a call to _exit(2) or exit(3)
        g_exit_value = WEXITSTATUS(status); // evaluates to the low-order 8 bits of the argument passed to _exit(2) or exit(3) by the child.
}