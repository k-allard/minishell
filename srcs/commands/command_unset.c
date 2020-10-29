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

void    delete_elem(t_list *lst)
{
    free(((t_env *)lst->content)->key);
    free(((t_env *)lst->content)->value);
    free(lst->content);
    free(lst); 
}

void    command_unset(char **argv, t_list *envs, int i)
{
    t_list  *tmp;
    t_list  *del;

    while (argv[++i])
    {
        tmp = envs;
        while (tmp && (is_this_key_env(argv[i], tmp)))
        {
            del = tmp;
            tmp = tmp->next;
            delete_elem(del);
        }
        while (tmp->next)
        {
            if (is_this_key_env(argv[i], tmp->next))
            {
                del = tmp->next;
                tmp->next = tmp->next->next;
                delete_elem(del);
            }
            else
                tmp = tmp->next;
        }
    }
}
