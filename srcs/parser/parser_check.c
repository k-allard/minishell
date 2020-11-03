# include "../minishell.h"
#include "../t_lexema/t_lexema.h"

static int is_marker(t_lexema *lexema)
{
    if(lexema == NULL)
        return 0;
    if(lexema->lexemaType == lexema_type_redirect_from ||
    lexema->lexemaType == lexema_type_redirect_to_append ||
    lexema->lexemaType == lexema_type_redirect_to ||
    lexema->lexemaType == lexema_type_semicolon ||
    lexema->lexemaType == lexema_type_pipe)
        return 1;
    else
        return 0;
}

static int is_block(t_lexema *lexema)
{
    if(lexema == NULL)
        return 0;
    if(lexema->lexemaType == lexema_type_simple_word ||
       lexema->lexemaType == lexema_type_single_q ||
       lexema->lexemaType == lexema_type_double_q)
        return 1;
    else
        return 0;
}

/**
 * Корректно:
 *  1. NULL + block
 *  2. block + block
 *  3. block + marker(any)
 *  4. marker(any) + block
 *  5. marker(;) + marker(<)
 *  6. marker(;) + marker(>)
 *  7. marker(;) + marker(>>)
 *  8. marker(|) + marker(<)
 *  9. marker(|) + marker(>)
 * 10. marker(|) + marker(>>)
 *
 * Некорректно - marker(any) + marker(any), кроме 6-ти вариантов № 5,6,7,8,9,10 выше:
 *  marker(;) + marker(;)
 *  marker(;) + marker(|)
 *
 *  marker(|) + marker(;)
 *  marker(|) + marker(|)
 *
 *  marker(>) + marker(<)
 *  marker(>) + marker(;)
 *  marker(>) + marker(|)
 *  marker(>) + marker(>)
 *  marker(>) + marker(>>)
 *
 *  marker(>>) + marker(<)
 *  marker(>>) + marker(;)
 *  marker(>>) + marker(|)
 *  marker(>>) + marker(>)
 *  marker(>>) + marker(>>)
 */
static int is_sequence_correct(t_lexema *lexema_prev, t_lexema *lexema)
{
    if(lexema_prev == NULL)
        return(is_block(lexema));
    else
    {
        if(is_marker(lexema_prev) && is_marker(lexema))
        {
            if((lexema_prev->string[0] == ';' || lexema_prev->string[0] == '|') &&
                    (lexema->string[0] == '>' || lexema->string[0] == '<'))
                return 1;
            else
                return 0;
        }
        else
            return 1;
    }
}

int check_marker_syntaxis(t_list_lexema *lexema_list)
{
    t_lexema *lexema_prev;
    t_lexema *lexema;
    int is_correct = 1;

    lexema_prev = NULL;
    while (lexema_list && is_correct)
    {
        lexema = lexema_list->lexema;
        if((is_correct = is_sequence_correct(lexema_prev, lexema)))
        {
            lexema_prev = lexema;
            lexema_list = lexema_list->next;
        }
    }
    is_correct = (is_correct && !is_marker(lexema));
    if(!is_correct)
    {
        ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
        ft_putstr_fd(lexema->string, STDERR_FILENO);
        ft_putendl_fd("\'", STDERR_FILENO);
        return (258);
    }
    return (0);
}
