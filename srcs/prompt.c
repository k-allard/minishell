/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 14:47:11 by kallard           #+#    #+#             */
/*   Updated: 2020/11/02 18:35:31 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	write_prompt(void)
{
	ft_putstr_fd(" \033[31mFA\033[0m\033[32mST\033[0m\033[33mES", 2);
	ft_putstr_fd("\033[0m\033[34mT\033[0m\033[35mSHELL\033[0m$ ", 2);
}
