/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwindom <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 03:05:00 by cwindom           #+#    #+#             */
/*   Updated: 2020/10/23 03:05:02 by cwindom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void add_new(t_list *envs, char *new_env, char *new_data)
{
	t_env *new;
	new = (t_env *)malloc(sizeof(t_env));
	new->key = (char *)malloc(sizeof(char) * ft_strlen(new_env));
	new->key = ft_strcpy(new->key, new_env);
	new->value = (char *)malloc(sizeof(char) * ft_strlen(new_data));
	new->value = ft_strcpy(new->value, new_data);
	ft_lstadd_back(&envs, ft_lstnew(new));
}

int update_data(t_list *envs, char *new_env, char *new_data)
{
	int flag;

	flag = 0;
	while (envs->next)
    {
            if (is_this_key_env(new_env, envs))
            {
				free(((t_env *)envs->content)->value);
				((t_env *)envs->content)->value = 
				(char *)malloc(ft_strlen(new_data));
				ft_strcpy(((t_env *)envs->content)->value, new_data);
             	printf("Нашлась!\n");//
				 flag = 1;
             	break ;
            }
            envs = envs->next;
    }
	return (flag);
}

void check_env(char *argv, t_list *envs)
{
	char *new_env;
	char *new_data;
	int len_ravno;
	int len_data;
	int i;

	len_ravno = 0;
	i = -1;
	while (argv[len_ravno] != '=')
		len_ravno++;
	new_env = (char *)malloc((len_ravno + 1) * sizeof(char));
	while (argv[++i] != '=')
		new_env[i] = argv[i];
	new_env[i] = '\0';
	i = -1;
	len_data = ft_strlen(argv) - len_ravno;
	new_data = (char *)malloc((len_data + 1) * sizeof(char));
	while (argv[len_ravno] != '\0')
		new_data[++i] = argv[++len_ravno];
	new_data[i] = '\0';
	printf("новая переменная: %s\n", new_env);//
	printf("новая дата: %s\n", new_data);//
	if (!update_data(envs, new_env, new_data))
		add_new(envs, new_env, new_data);
	free(new_env);
	free(new_data);
}

void command_export(char **argv, t_list *envs)
{
    int i;

    i = 0;
    if (count_argv(argv) < 2)
         command_env_declare(envs);
	else
    	while (argv[++i])
    	{
			if (!valid_name_first(argv[i][0]))
			{
				printf("export: '%s' : not a valid identifier\n", argv[i]);
			}
			if (ft_strchr(argv[i], '=') && valid_name_first(argv[i][0]))
				check_env(argv[i], envs);
    	}
}
