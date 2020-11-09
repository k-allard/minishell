#include "../minishell.h"
#include "parser.h"

static void unescape(char **str_eval, char **str_original)
{
    str_join_str(str_eval, "$");
    (*str_original)+=2;
}

static void simple_join_symbol(char **str_eval, char **str_original)
{
    str_join_char(str_eval, **str_original);
    (*str_original)++;
}

static void eval_vars_and_params(char **str_eval, char **str_original, int argc, char **argv, t_list_env	*envs)
{
    if (*((*str_original) + 1) == '?')
        eval_last_exit_value(str_eval, str_original); //$? substitution
    else if(is_var_name_symbol(*((*str_original)+1)))
    {
        eval_var(str_eval, str_original, envs);
    } else if(is_var_name_symbol_with_num(*((*str_original)+1)))
    {
        eval_param(str_eval, str_original, argc, argv);
    } else
        simple_join_symbol(str_eval, str_original);
}

static void eval_vars_and_unescape(t_lexema *lexema, int argc, char **argv, t_list_env	*envs)
{
    char *str_original;
    char *str_eval;

    str_eval = ft_strdup("");
    str_original = lexema->string;
    if (*str_original == '~' && *(str_original+1) == '\0')
    {
        eval_tilda(&str_eval, &str_original, envs);
    }
    else
        while (*str_original)
        {
            if(*str_original == '\\' && *(str_original+1) == '$')
                unescape(&str_eval, &str_original);
            else if (*str_original == '$')
                eval_vars_and_params(&str_eval, &str_original, argc, argv, envs);
            else
                simple_join_symbol(&str_eval, &str_original);
        }
    free(lexema->string);
    lexema->string = str_eval;
}

void eval_vars_and_unescape_in_lexema_chain(t_list_lexema *lexema_chain, int argc, char **argv, t_list_env *envs)
{
    t_lexema *lexema;

    while (lexema_chain)
    {
        lexema = lexema_chain->lexema;
        if(lexema->lexema_type == lexema_type_simple_word || lexema->lexema_type == lexema_type_double_q)
        {
            eval_vars_and_unescape(lexema, argc, argv, envs);
        }
        lexema_chain = lexema_chain->next;
    }
}