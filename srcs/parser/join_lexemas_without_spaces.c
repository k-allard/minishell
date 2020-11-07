#include "../minishell.h"
#include "../t_lexema/t_lexema.h"
#include "parser.h"

void join_lexemas_without_spaces(t_list_lexema *lexema_chain)
{
    t_list_lexema *tmp;

    while (lexema_chain)
    {
        tmp = lexema_chain->next;
        if(is_block(lexema_chain->lexema) && tmp && is_block(tmp->lexema) && tmp->lexema->has_space_before == 0)
        {
            tmp = lexema_chain->next;
            str_join_str(&lexema_chain->lexema->string, tmp->lexema->string);
            lexema_chain->next = tmp->next;
            free(tmp->lexema->string);
            free(tmp->lexema);
            free(tmp);
        }
        else
            lexema_chain = lexema_chain->next;
    }
}