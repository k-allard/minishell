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

    res = -1;
    if(dup2(redirects->stdout_original, STDOUT_FILENO) != -1)
        if(dup2(redirects->stdin_original, STDIN_FILENO) != -1)
            if(close(redirects->stdout_original) != -1)
                if(close(redirects->stdin_original) != -1)
                    res = 0;
    if(res != 0)
    {
        ft_putendl_fd("Error restore STDIN or STDOUT after redirection", STDERR_FILENO);
    }

    if(redirects->stdout_fd != -1)
        if (close(redirects->stdout_fd) == -1)
            return error_close_fd("Close STDOUT file redirection error");
    if(redirects->stdin_fd != -1)
        if (close(redirects->stdin_fd) == -1)
            return error_close_fd("Close STDIN file redirection error");
    return (res);
}
