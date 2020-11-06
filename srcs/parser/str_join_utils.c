# include "../minishell.h"
#include "../t_lexema/t_lexema.h"

void str_join_str(char **str1, char *str2)
{
    char *str_tmp;

    str_tmp = ft_strjoin(*str1, str2);
    free(*str1);
    *str1 = str_tmp;
}

void str_join_char(char **str1, char ch)
{
    char *str_tmp;

    str_tmp = (char *)(malloc(sizeof(char )*2));
    str_tmp[0] = ch;
    str_tmp[1] = '\0';

    str_join_str(str1, str_tmp);
    free(str_tmp);
}