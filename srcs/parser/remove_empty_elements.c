# include "../minishell.h"
#include "../t_lexema/t_lexema.h"
#include "parser.h"

void remove_empty_elements(t_list_lexema **lexema_chain)
{
    t_list_lexema *prev;
    t_list_lexema *current;
    t_list_lexema *tmp;
    t_list_lexema *tmp2;
    char *tmp_string;

    prev = NULL;
    current = *lexema_chain;
    while (current)
    {
        if(current->lexema->string[0] == '\0')
        {
            if(current->lexema->lexemaType==lexema_type_simple_word)
            {
                if(prev == NULL)
                {
                    *lexema_chain = current->next;
                }
            }
            else {
                if (current->next) {
                    if (current->next->lexema->has_space_before) {
                        if((current->next->lexema->string[0] != '\0')) {
                            tmp_string = current->next->lexema->string;
                            current->next->lexema->string = ft_strjoin(" ", current->next->lexema->string);
                            free(tmp_string);
                        }
                    }
                    else
                    {
                        if(!(current->lexema->has_space_before) && prev)
                        {
                            tmp_string = prev->lexema->string;
                            prev->lexema->string = ft_strjoin(prev->lexema->string, current->next->lexema->string);
                            free(tmp_string);

                            tmp = current->next;
                            current->next = current->next->next;
                            free(tmp->lexema->string);
                            free(tmp->lexema);
                            free(tmp);
                        }
                    }
                }
            }
            tmp = current;
            current = current->next;
            if (prev)
            {
                prev->next = current;
                current = prev;
            }
            free(tmp->lexema->string);
            free(tmp->lexema);
            free(tmp);
            continue;
        }
        prev = current;
        current = current->next;
    }
}