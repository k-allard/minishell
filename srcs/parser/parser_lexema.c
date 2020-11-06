# include "../minishell.h"
#include "../t_lexema/t_lexema.h"


//static void t_lexema_list_free(t_list **lexema_list)
//{
//    ft_lstclear(lexema_list, t_lexema_free_void);
//}

static int is_blank(char symbol)
{
    if(symbol == ' ' || symbol == '\t')
        return 1;
    else
        return 0;
}

static int skip_blank(char**commandline)
{
	int has_space_before;

	has_space_before = 0;
    while (is_blank(**commandline))
    {
    	has_space_before = 1;
		(*commandline)++;
	}
	return has_space_before;
}

static void read_simple_symbol(char **commandline, t_lexema *lexema)
{
    char *symbol;
    char *tmpString;

    symbol = ft_strnew(2);
    tmpString = lexema->string;

    symbol[0] = *((*commandline)++);
    symbol[1] = '\0';

    lexema->string = ft_strjoin(tmpString, symbol);
    free(tmpString);
    free(symbol);
}

static int read_escape_symbol(char **commandline, t_lexema *lexema, int is_var_support)
{
    char *symbol;
    char *tmpString;
    char tmpSymbol;

    (*commandline)++;
    tmpSymbol = *((*commandline)++);
    if(!tmpSymbol)
        return (0);
    symbol = ft_strnew(2);
    tmpString = lexema->string;
    if(is_var_support && tmpSymbol == '$')
    {
        symbol[0] = '\\';
        symbol[1] = tmpSymbol;
    }
    else
        symbol[0] = tmpSymbol;

    lexema->string = ft_strjoin(tmpString, symbol);
    free(tmpString);
    free(symbol);
    return (0);
}

static int error_end_of_line(char quoteChar)
{
    ft_putstr_fd("unexpected EOF while looking for matching `", STDERR_FILENO);
    ft_putchar_fd(quoteChar, STDERR_FILENO);
    ft_putstr_fd("'\n", STDERR_FILENO);
    ft_putstr_fd("syntax error: unexpected end of file\n", STDERR_FILENO);
    return(2);
}
static int malloc_error(char *commandline)
{
    ft_putendl_fd("memory allocation error during command line processing", STDERR_FILENO);
    return(5);
}
static int read_quote_param(char **commandline, t_lexema *lexema, char quoteChar)
{
    (*commandline)++;
    while (lexema->string && **commandline && **commandline != quoteChar)
    {
        if(**commandline == '\\') {
            if (quoteChar == '"')
                read_escape_symbol(commandline, lexema, 1);
            else
                read_simple_symbol(commandline, lexema);
        }
        else
            read_simple_symbol(commandline, lexema);
    }
    if(lexema->string == NULL)
        return (malloc_error(*commandline));
    else if(**commandline == '\0')
        return (error_end_of_line(quoteChar));
    else
        (*commandline)++;
    lexema->lexemaType = (quoteChar == '"') ? lexema_type_double_q : lexema_type_single_q;
    return (0);
}

static int read_pipe(char **commandline, t_lexema *lexema)
{
    read_simple_symbol(commandline, lexema);
    if(lexema->string == NULL)
        return (malloc_error(*commandline));
    lexema->lexemaType = lexema_type_pipe;
    return (0);
}
static int read_semicolon(char **commandline, t_lexema *lexema)
{
    read_simple_symbol(commandline, lexema);
    if(lexema->string == NULL)
        return (malloc_error(*commandline));
    lexema->lexemaType = lexema_type_semicolon;
    return (0);
}
static int read_redirect_to(char **commandline, t_lexema *lexema)
{
    int i;

    i = 0;
    while (lexema->string && **commandline && **commandline == '>' && i++ < 2)
    {
        read_simple_symbol(commandline, lexema);
    }
    if(lexema->string == NULL)
        return (malloc_error(*commandline));
    lexema->lexemaType = (i == 1) ? lexema_type_redirect_to : lexema_type_redirect_to_append;
    return (0);
}
static int read_redirect_from(char **commandline, t_lexema *lexema)
{
    int i;

    i = 1;
    while (lexema->string && **commandline && **commandline == '<' && i++ <= 1)
    {
        read_simple_symbol(commandline, lexema);
    }
    if(lexema->string == NULL)
        return (malloc_error(*commandline));
    lexema->lexemaType = lexema_type_redirect_from;
    return (0);
}

static int is_simple_symbol(char symbol)
{
    char *non_simple_symbols;

    non_simple_symbols = "'\" \t<>|;";
    if(ft_strchr(non_simple_symbols, (int)symbol))
        return 0;
    else
        return 1;
}

static int read_simple_word(char **commandline, t_lexema *lexema)
{
    while (lexema->string && **commandline && is_simple_symbol(**commandline))
    {
        if(**commandline == '\\')
            read_escape_symbol(commandline, lexema, 1);
        else
            read_simple_symbol(commandline, lexema);
    }
    if(lexema->string == NULL)
        return (malloc_error(*commandline));
    lexema->lexemaType = lexema_type_simple_word;
    return (0);
}

static t_lexema *get_next_lexema(char **commandline, int *res)
{
    t_lexema *lexema;
    int has_space_before;

    *res = 0;
	has_space_before = skip_blank(commandline);
    if(**commandline == '\0') return NULL;
    lexema = t_lexema_init();
    if(**commandline == '"') *res = read_quote_param(commandline, lexema, '"'); else
    if(**commandline == '\'') *res = read_quote_param(commandline, lexema, '\''); else
    if(**commandline == '|') *res = read_pipe(commandline, lexema); else
    if(**commandline == ';') *res = read_semicolon(commandline, lexema); else
    if(**commandline == '>') *res = read_redirect_to(commandline, lexema); else
    if(**commandline == '<') *res = read_redirect_from(commandline, lexema); else
        *res = read_simple_word(commandline, lexema);
	lexema->has_space_before = has_space_before;
    return lexema;
}

t_list_lexema *get_lexema_list(char *commandline, int *res)
{
    t_lexema *lexema;
    t_list *lexema_list;

    lexema_list = NULL;
    while ((lexema = get_next_lexema(&commandline, res)) && (*res == 0))
    {
        ft_lstadd_back(&lexema_list, ft_lstnew(lexema));
    }
    return (t_list_lexema *)lexema_list;
}
