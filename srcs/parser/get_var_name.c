/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_name.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwindom <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 02:50:03 by cwindom           #+#    #+#             */
/*   Updated: 2020/11/09 02:50:06 by cwindom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

char		*get_var_name(char *str)
{
	int		i;
	char	*var_name;

	i = 1;
	while (str[i] && is_var_name_symbol_with_num(str[i]))
		i++;
	var_name = ft_strndup((str + 1), i - 1);
	return (var_name);
}
