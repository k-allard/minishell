/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 22:38:46 by kallard           #+#    #+#             */
/*   Updated: 2020/10/15 00:34:27 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

t_var *new_var(char *name, char *value, int is_env)
{
	t_var *var;

	if (!(var = malloc(sizeof(t_var))))
		return (0);
	var->is_env = is_env;
	var->name = name;
	var->value = value;
	return (var);
}

t_list *get_env_vars(char **env)
{
	t_list	*first;
	t_list	*temp;
	t_var	*var;
	char	*name_temp;
	char	*value_temp;

	first = 0;
	while (*env)
	{
		if (!(name_temp = ft_strndup(*env, ft_strchr(*env, '=') - *env)))
			return (0);
		if (!(value_temp = ft_strdup(ft_strchr(*env, '=') + 1)))
			return (0);
		if (!(var = new_var(name_temp, value_temp, 1)))
			return (0);
		if (!(temp = ft_lstnew(var)))
			return (0);
		ft_lstadd_back(&first, temp);
		env++;
	}
	return (first);
}

int main(int argc, char **argv, char **envp)
{
    char    *input;
    t_list  *env_list;
    t_lexer lex;

    argc = 0;
    argv = NULL;
	input = NULL;
    if(!(env_list = get_env_vars(envp)))
		return (0);
    init_lexer(&lex, NULL, env_list);

	while (1)
	{
		free(input);
		input = NULL;
		ft_putstr_fd("(¯\_(ツ)_/¯) ", 1);
		if (!get_next_line(0, &input))
		{
			ft_printf("exit\n");
			return (0);
		}
		
		//лексер нужно ресетнуть

	}
	return (0);
    
	
}
