/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 22:43:39 by kallard           #+#    #+#             */
/*   Updated: 2020/10/23 15:46:54 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** For each name, unset removes the corresponding variable (set to NULL?). 
** The variables PATH, PS1, PS2, MAILCHECK, and IF cannot be unset.
*/

//есть два случая: если мы удаляем корень списка и если мы удаляем любой элемент из середины
//как узнать какой случай?
t_list * delete_head(t_list *root) //пригодится для удаления корня если такое
{
  t_list *temp;
  temp = root->next;
  free(root); // освобождение памяти текущего корня
  return(temp); // новый корень списка
}
static void delete_elem(t_list *lst)
{
    //t_list *temp;
   
    //temp->next = lst->next; // переставляем указатель
    free(((t_env *)lst->content)->key);
    free(((t_env *)lst->content)->value);
    free(lst->content);
    free(lst); 
    //return(temp); //возвращаем указатель на следующий элемент
}

void	command_unset(char **argv, t_list *envs)
{
	int	i;
	i = 0; //-1
    t_list *tmp;
    t_list *head;
    t_list *del;

    int n = 0;
    while (argv[++i]) // 1
    {
        tmp = envs;
        printf("%s\n", "go while");

        
        
        while (tmp && (is_this_key_env(argv[i], tmp)))
        {
            n++;//2
            printf("%d\n", n);

            del = tmp;
            tmp = tmp->next;
            delete_elem(del);
            printf("%s", "unset success");
        }

        while (tmp->next)//
        {
            n++;//2
            printf("%d\n", n);
            if (is_this_key_env(argv[i], tmp->next))
            {
                del = tmp->next;
                tmp->next = tmp->next->next;
                delete_elem(del);
                printf("%s", "unset success");
            }
            else
                tmp = tmp->next;
        }
    }
}

