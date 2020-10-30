# include "../minishell.h"
#include "../t_lexema/t_lexema.h"

static t_list *t_lexema_list_item_init(t_lexema *lexema)
{

}

static void t_lexema_list_free(t_list **lexema_list)
{
    ft_lstclear(lexema_list, t_lexema_free_void);
}

static int is_blank(char symbol)
{
    if(symbol == ' ' || symbol == '\t')
        return 1;
    else
        return 0;
}

static void skip_blank(char**commandline)
{
    while (is_blank(**commandline))
        (*commandline)++;
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

static void error_end_of_line_escape()
{
    ft_putstr_fd("неожиданный конец строки после «\\», во время поиска экранированного символа\n", STDERR_FILENO);
    ft_putstr_fd("синтаксическая ошибка: неожиданный конец строки\n", STDERR_FILENO);
    exit(6);
}

static void read_escape_symbol(char **commandline, t_lexema *lexema, int is_var_support)
{
    char *symbol;
    char *tmpString;
    char tmpSymbol;

    symbol = ft_strnew(2);
    tmpString = lexema->string;

    (*commandline)++;
    tmpSymbol = *((*commandline)++);
    if(!tmpSymbol)
        error_end_of_line_escape();
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
}

static void error_end_of_line(char quoteChar)
{
    ft_putstr_fd("неожиданный конец строки во время поиска «", STDERR_FILENO);
    ft_putchar_fd(quoteChar, STDERR_FILENO);
    ft_putstr_fd("»\n", STDERR_FILENO);
    ft_putstr_fd("синтаксическая ошибка: неожиданный конец строки\n", STDERR_FILENO);
    exit(4);
}
static void malloc_error(char *commandline)
{
    ft_putstr_fd("ошибка выделения памяти при обработке командной строки «", STDERR_FILENO);
    ft_putstr_fd(commandline, STDERR_FILENO);
    ft_putstr_fd("»\n", STDERR_FILENO);
    exit(5);
}
static void read_quote_param(char **commandline, t_lexema *lexema, char quoteChar)
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
        malloc_error(*commandline);
    else if(**commandline == '\0')
        error_end_of_line(quoteChar);
    else
        *((*commandline)++);
    lexema->lexemaType = (quoteChar == '"') ? lexema_type_double_q : lexema_type_single_q;
}

static void read_pipe(char **commandline, t_lexema *lexema)
{
    read_simple_symbol(commandline, lexema);
    if(lexema->string == NULL)
        malloc_error(*commandline);
    lexema->lexemaType = lexema_type_pipe;
}
static void read_semicolon(char **commandline, t_lexema *lexema)
{
    read_simple_symbol(commandline, lexema);
    if(lexema->string == NULL)
        malloc_error(*commandline);
    lexema->lexemaType = lexema_type_semicolon;
}
static void read_redirect_to(char **commandline, t_lexema *lexema)
{
    int i;

    i = 0;
    while (lexema->string && **commandline && **commandline == '>' && i++ < 2)
    {
        read_simple_symbol(commandline, lexema);
    }
    if(lexema->string == NULL)
        malloc_error(*commandline);
    lexema->lexemaType = (i == 1) ? lexema_type_redirect_to : lexema_type_redirect_to_append;
}
static void read_redirect_from(char **commandline, t_lexema *lexema)
{
    int i;

    i = 1;
    while (lexema->string && **commandline && **commandline == '<' && i++ <= 1)
    {
        read_simple_symbol(commandline, lexema);
    }
    if(lexema->string == NULL)
        malloc_error(*commandline);
    lexema->lexemaType = lexema_type_redirect_from;
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

static void read_simple_word(char **commandline, t_lexema *lexema)
{
    while (lexema->string && **commandline && is_simple_symbol(**commandline))
    {
        if(**commandline == '\\')
            read_escape_symbol(commandline, lexema, 1);
        else
            read_simple_symbol(commandline, lexema);
    }
    if(lexema->string == NULL)
        malloc_error(*commandline);
    lexema->lexemaType = lexema_type_simple_word;
}

static t_lexema *get_next_lexema(char **commandline)
{
    t_lexema *lexema;

    skip_blank(commandline);
    if(**commandline == '\0') return NULL;
    lexema = t_lexema_init();
    if(**commandline == '"') read_quote_param(commandline, lexema, '"'); else
    if(**commandline == '\'') read_quote_param(commandline, lexema, '\''); else
    if(**commandline == '|') read_pipe(commandline, lexema); else
    if(**commandline == ';') read_semicolon(commandline, lexema); else
    if(**commandline == '>') read_redirect_to(commandline, lexema); else
    if(**commandline == '<') read_redirect_from(commandline, lexema); else
    read_simple_word(commandline, lexema);

    return lexema;
}

t_list_lexema *get_lexema_list(char *commandline)
{
    t_lexema *lexema;
    t_list *lexema_list;

    lexema_list = NULL;
    while ((lexema = get_next_lexema(&commandline)))
    {
        ft_lstadd_back(&lexema_list, ft_lstnew(lexema));
    }
    return (t_list_lexema *)lexema_list;
}