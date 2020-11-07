# include "../minishell.h"

#include "t_lexema.h"

/*
** Memory allocation and initialization of the new lexema element
** Returns NULL if the memory was not allocated, and t_lexema if it was
*/

t_lexema* t_lexema_init()
{
    t_lexema *lexema;
    lexema = (t_lexema *)malloc(sizeof(t_lexema));
    if(lexema != NULL)
    {
        lexema->lexemaType = lexema_type_default;
        lexema->has_space_before = 0;
        lexema->string = (char *)malloc(sizeof(char ));
        if(lexema->string != NULL)
            lexema->string[0] = '\0';
    }
    return lexema;
}

//static void t_lexema_free(t_lexema *lexema)
//{
//    if(lexema != NULL)
//    {
//        if(lexema->string != NULL)
//            free(lexema->string);
//        lexema->string = NULL;
//        free(lexema);
//    }
//}

//void t_lexema_free_void(void *content)
//{
//    t_lexema *lexema;
//
//    lexema = (t_lexema *)content;
//    t_lexema_free(lexema);
//}
