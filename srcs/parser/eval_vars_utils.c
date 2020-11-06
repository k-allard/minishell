# include "../minishell.h"
#include "../t_lexema/t_lexema.h"
#include "parser.h"

void eval_var(char **str_eval, char **str_original, t_list_env	*envs)
{
    char *varName;

    varName = get_var_name(*str_original);
    str_join_str(str_eval, get_env_value(varName, (t_list *)envs));
    (*str_original)+=(ft_strlen(varName)+1);
    free(varName);
}

void eval_param(char **str_eval, char **str_original, int argc, char **argv)
{
    int paramIndex;

    paramIndex = (*((*str_original)+1)) - '0';
    if(paramIndex < argc)
    {
        str_join_str(str_eval, argv[paramIndex]);
    }
    (*str_original)+=2;
}



void eval_last_exit_value(char **str_eval, char **str_original) //$? substitution
{
    char *exit_value;

    exit_value = ft_itoa(g_exit_value);
    str_join_str(str_eval, exit_value);
    (*str_original)+=(ft_strlen(exit_value)+1);
    free(exit_value);
}

void eval_tilda(char **str_eval, char **str_original, t_list_env	*envs) //~ substitution
{
    char *home_dir;

    home_dir = get_env_value("HOME", (t_list *)envs);
    str_join_str(str_eval, home_dir);
    (*str_original)+=2;
}