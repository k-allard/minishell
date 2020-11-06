# include "../minishell.h"
# include "parser.h"
#include <unistd.h>
#include <errno.h>


static int error_close_fd(char *str)
{
    ft_putendl_fd(strerror(errno), STDERR_FILENO);
    if(str != NULL)
        ft_putendl_fd(str, STDERR_FILENO);
    return (-1);

}

int t_redirects_close(t_redirects *redirects)
{
    int res;

    res = 0;
    if((redirects->stdout_fd != -1) && (close(redirects->stdout_fd) == -1))
        res = error_close_fd("Close STDOUT file redirection error");
    if((redirects->stdin_fd != -1) && (close(redirects->stdin_fd) == -1))
        res = error_close_fd("Close STDIN file redirection error");
    if((redirects->stdout_original != -1) && (dup2(redirects->stdout_original, STDOUT_FILENO) == -1))
        res = error_close_fd("Error restore STDOUT after redirection");
    if((redirects->stdin_original != -1) && (dup2(redirects->stdin_original, STDIN_FILENO) == -1))
        res = error_close_fd("Error restore STDIN after redirection");
    return (res);
}
