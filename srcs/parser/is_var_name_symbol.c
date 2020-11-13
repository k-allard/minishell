/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_var_name_symbol.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwindom <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 03:50:33 by cwindom           #+#    #+#             */
/*   Updated: 2020/11/09 03:50:37 by cwindom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_var_name_symbol(char symbol)
{
	if (((symbol >= 'a') && (symbol <= 'z')) ||
	((symbol >= 'A') && (symbol <= 'Z')) || symbol == '_')
		return (1);
	else
		return (0);
}

int	is_var_name_symbol_with_num(char symbol)
{
	if ((symbol >= '0' && symbol <= '9') ||
	is_var_name_symbol(symbol))
		return (1);
	else
		return (0);
}
