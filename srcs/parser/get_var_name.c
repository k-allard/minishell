# include "../minishell.h"
#include "parser.h"


char *get_var_name(char *str)
{
    int i;
    char *varName;

    i = 1;
    while (str[i] && is_var_name_symbol_with_num(str[i]))
        i++;
    varName = ft_strndup((str+1), i-1);
    return varName;
}