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

void command_cd(/*int argc, */char **argv)
{
	DIR		*dir; //Тип, представляющий поток каталога
	char	*path;
    int		er; //можно положить в структуру с ошибками

	er = 0;
	//if (argc > 1) //если после cd есть путь
		path = argv[1];
	//else //если путь не указан
        //printf("%s", "Здесь будет какой-то код чтобы попасть в Home");
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
	//if (er)
     //   printf("%s", "вывести ошибку с помощью strerror(errno)");
}
