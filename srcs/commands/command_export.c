/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 03:05:00 by cwindom           #+#    #+#             */
/*   Updated: 2020/10/31 15:39:12 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_argv(char **argv)
{
	int i;
	i = 0;

	while (argv[i])
	{
		i++;
	}
	return (i);
}

void		command_env_declare(t_list *envs)
{
	if (!envs)
		return ;
    ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(((t_env *)envs->content)->key, 1);
	ft_putchar_fd('=', 1);
	ft_putendl_fd(((t_env *)envs->content)->value, 1);
	command_env_declare(envs->next);
}

void check_env(char *argv, t_list *envs)
{
	char *new_env;
	char *new_data;
	int len_ravno;
	int len_data;
	int i;
	t_list *temp;

	temp = envs;
	len_ravno = 0;
	i = 0;
	while (argv[len_ravno] != '=')
		len_ravno++;
	new_env = (char *)malloc((len_ravno + 1) * sizeof(char));
	while (argv[i] != '=')
	{
		new_env[i] = argv[i];
		i++;
	}
	new_env[i] = '\0';
	len_ravno++;
	i = 0;
	len_data = ft_strlen(argv) - len_ravno;
	new_data = (char *)malloc((len_data + 1) * sizeof(char));
	while (argv[len_ravno] != '\0')
	{
		new_data[i] = argv[len_ravno];
		i++;
		len_ravno++;
	}
	new_data[i] = '\0';
	printf("новая переменная: %s\n", new_env);
	printf("новая дата: %s\n", new_data);
    while (temp->next)
    {
            if (is_this_key_env(new_env, temp))
            {
             printf("Нашлась!\n");
             break ;
            }
            else
                temp = temp->next;
    }	
    if (is_this_key_env(new_env, envs))
		printf("меняем значение");
	else 
		printf("Выделяем память и добавляем новый аргумент");
	
	//command_env(envs); //с самим списком все норм, выводит все переменные
	free(new_env);
	free(new_data);
}

int command_export(char **argv, t_list *envs) //что если переменная есть и по
{
    int i;
    int j;
    int n;

    i = 0;
    j = 0;
    n = count_argv(argv);
    if (n < 2) //если просто export то нужно вывести список переменных с приставкой "declare -x "
    {
         command_env_declare(envs); //готово
         return (0); // готово
    }
    while (argv[++i])
    {
		if (ft_strchr(argv[i], '=') && !ft_isalpha(argv[i][0])) //проверяем ошибку
		{
			printf("export: '%s' : not a valid identifier\n", argv[i]);
		}
		if (ft_strchr(argv[i], '=') && ft_isalpha(argv[i][0])) //условно из альфа но на на самом деле можно больше, например с нижнего подчеркивания. если пришло только равно без символа то надо ошибку
		{
			check_env(argv[i], envs);
				//идем в функцию которая проверяет есть ли такая переменная, если есть
				//меняет ее значение, если нет - устанавливает такую новую, то есть выделяет память
				//j = 0;
				//while (argv[i][j] != '=')
            	//{
                //	printf("%c", argv[i][j]);
				//	j++;
            	//}
		}
    }
	return (0); //TODO: код возврата 1 если некорректный идентификатор. Пример: export 123
}
