/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 03:05:00 by cwindom           #+#    #+#             */
/*   Updated: 2020/11/11 11:32:02 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		command_env_declare(t_list_env *envs)
{
	if (!envs)
		return ;
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(envs->env->key, 1);
	ft_putstr_fd("=\"", 1);
	ft_putstr_fd(envs->env->value, 1);
	ft_putendl_fd("\"", 1);
	command_env_declare(envs->next);
}

void		add_new(t_list_env *envs, char *new_env, char *new_data)
{
	t_env *new;

	new = (t_env *)malloc(sizeof(t_env));
	new->key = ft_strdup(new_env);
	new->value = ft_strdup(new_data);
	ft_lstadd_back((t_list**)(&envs), ft_lstnew(new));
}

int			update_env_data(t_list_env *envs, char *new_env, char *new_data)
{
	int flag;

	flag = 0;
	while (envs)
	{
		if (is_this_key_env(new_env, envs))
		{
			free(envs->env->value);
			envs->env->value = ft_strdup(new_data);
			flag = 1;
			break ;
		}
		envs = envs->next;
	}
	return (flag);
}

void		check_env(char *argv, t_list_env *envs)
{
	char	*new_env;
	char	*new_data;
	int		len_ravno;
	int		len_data;
	int		i;

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
	if (!update_env_data(envs, new_env, new_data))
		add_new(envs, new_env, new_data);
	free(new_env);
	free(new_data);
}

int			command_export(char **argv, t_list_env *envs)
{
	int i;

	i = 0;
	if (count_argv(argv) < 2)
		command_env_declare(envs);
	else
		while (argv[++i])
		{
			if (!valid_name_first(argv[i][0]) || !valid_name(argv[i]))
			{
				ft_putstr_fd("export: `", 2);
				ft_putstr_fd(argv[i], 2);
				ft_putendl_fd("': not a valid identifier", 2);
				return (1);
			}
			if (ft_strchr(argv[i], '='))
				check_env(argv[i], envs);
		}
	return (0);
}
