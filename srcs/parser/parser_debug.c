# include "../minishell.h"
#include "../t_lexema/t_lexema.h"
void parser_debug_print_lexema_list(t_list_lexema *lexema_list)
{
    t_lexema *lexema;
    char *i_string;

    while (lexema_list)
    {
        lexema = lexema_list->lexema;
        i_string = ft_itoa(lexema->lexemaType);
        ft_putstr_fd(i_string, STDERR_FILENO);
        free(i_string);
		ft_putstr_fd("\t-\t«", STDERR_FILENO);
		if(lexema->has_space_before)
			ft_putstr_fd("space+", STDERR_FILENO);
		else
			ft_putstr_fd("space-", STDERR_FILENO);
		ft_putstr_fd("\t-\t«", STDERR_FILENO);
        ft_putstr_fd(lexema->string, STDERR_FILENO);
        ft_putstr_fd("»\n", STDERR_FILENO);
        lexema_list = lexema_list->next;
    }
}