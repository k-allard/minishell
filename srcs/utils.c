/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 19:42:19 by kallard           #+#    #+#             */
/*   Updated: 2020/10/21 21:28:57 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	free_double_array(char **array)
{
	int		i;

	if (!array)
		return ;
	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

int		error_no_cmd(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	return (127);
}

//int		error_no_file_dir(char *cmd)
//{
//	ft_putstr_fd(cmd, 2);
//	ft_putendl_fd(": No such file or directory", 2);
//	return (127);
//}
