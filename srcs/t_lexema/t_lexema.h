#ifndef FT_MINISHELL_T_LEXEMA_H
#define FT_MINISHELL_T_LEXEMA_H

typedef enum e_lexema_type
{
    lexema_type_default = 0,
    lexema_type_simple_word,
    lexema_type_double_q,
    lexema_type_single_q,
    lexema_type_marker,
    lexema_type_semicolon,
    lexema_type_redirect,
    lexema_type_redirect_to_append,
    lexema_type_redirect_to,
    lexema_type_redirect_from,
    lexema_type_pipe
} t_lexema_type;

typedef struct s_lexema
{
    char *string;
    t_lexema_type lexemaType;
} t_lexema;

t_lexema* t_lexema_init();
void t_lexema_free_void(void *content);

#endif //FT_MINISHELL_T_LEXEMA_H
