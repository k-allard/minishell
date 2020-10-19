#include "minishell.h"

void read_double_q_param(char** commandline)
{

}

void read_single_q_param(char** commandline)
{

}

void is_prev_command_exist(char symbol)
{
    if(current_cimmand_index = 0)
    {
        ft_putstr_fd("minishell: syntax error near unexpected token `", STDERR_FILENO);
        ft_putchar_fd(symbol, STDERR_FILENO);
        ft_putchar_fd('\'', STDERR_FILENO);
        exit(1);
    }
}
void read_pipe(char** commandline)
{
    int filedes[2];

    if(pipe(&filedes))
    {
        is_prev_command_exist('|');
        update_prev_command_output(filedes[1]);
        create_new_command(filedes[0]);
    }
}

void read_semicolon(char** commandline)
{
    is_prev_command_exist(';');
    create_new_command(STDIN_FILENO);
    parce_current_command(commandline);
}

void read_simple_word(char** commandline)
{

}

void read_simple_word(char** commandline)
{

}

void skip_space(char** commandline)
{

}

void parce_current_command(char* commandline)
{
    skip_space(&commandline);
    if(commandline[0] == '\0') 
        return;
    if(commandline[0] == '"') 
        read_double_q_param(&commandline);
    else if(commandline[0] == '\'')
        read_single_q_param(&commandline);
    else if(commandline[0] == '|')
        read_pipe(&commandline);
    else if(commandline[0] == ';')
        read_semicolon(&commandline);
    else if(commandline[0] == '$')
        read_variable(&commandline);
    else if(commandline[0] == '>')
        read_redirect_to(&commandline);
    else if(commandline[0] == '<')
        read_redirect_from(&commandline);
    else
        read_simple_word(&commandline);
}

void create_new_command(int filedes_input)
{

}

void parce_new_command(char* commandline)
{
    create_new_command(STDIN_FILENO);
    parce_current_command(&commandline);
}