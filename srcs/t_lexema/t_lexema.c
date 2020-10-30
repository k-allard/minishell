# include "../minishell.h"

#include "t_lexema.h"

/**
 * Выделение памяти и инициализация пустыми значениями нового элемента lexema
 * @return NULL, если память не была выделена, t_lexema, если память была выделена
 */
t_lexema* t_lexema_init()
{
    t_lexema *lexema;
    lexema = (t_lexema *)malloc(sizeof(t_lexema));
    if(lexema != NULL)
    {
        lexema->lexemaType = lexema_type_default;
        lexema->string = (char *)malloc(sizeof(char ));
        if(lexema->string != NULL)
            lexema->string[0] = '\0';
    }
    return lexema;
}

static void t_lexema_free(t_lexema *lexema)
{
    if(lexema != NULL)
    {
        if(lexema->string != NULL)
            free(lexema->string);
        lexema->string = NULL;
        free(lexema);
    }
}

void t_lexema_free_void(void *content)
{
    t_lexema *lexema;

    lexema = (t_lexema *)content;
    t_lexema_free(lexema);
}


