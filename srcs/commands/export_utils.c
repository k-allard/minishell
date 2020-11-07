/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwindom <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 21:26:36 by cwindom           #+#    #+#             */
/*   Updated: 2020/10/28 21:26:39 by cwindom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	valid_name_first(int ch)
{
	if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
		return (1);
	if (ch == '_')
		return (1);
	return (0);

}

int valid_name(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isalpha(str[i]) || ft_isdigit(str[i] || str[i] == '_'))
		{
			i++;
		}
		else
		{
			return (0);
		}

	}
	return (1);
}
