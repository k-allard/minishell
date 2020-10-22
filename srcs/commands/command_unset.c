/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 22:43:39 by kallard           #+#    #+#             */
/*   Updated: 2020/10/19 16:20:09 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** For each name, unset removes the corresponding variable (set to NULL?). 
** The variables PATH, PS1, PS2, MAILCHECK, and IF cannot be unset.
*/


/*void	command_unset(char **argv, t_list *envs, t_all all)
{
	int	i;

	i = 1;
 
    while (envs->next)
    {
        if (is_this_key_env(argv[i], envs))
        {
            

            return ;
        }
        //envs = envs->next;
    }
}*/

