# include "../minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../t_lexema/t_lexema.h"
#include "../t_stream/t_stream.h"
#include "../t_command/t_command.h"
#include "parser.h"

static int is_pipe_in_lexema_chain(t_list_lexema *lexema_chain)
{
    int is_pipe = 0;
    while (lexema_chain && !is_pipe)
    {
        if(lexema_chain->lexema->lexemaType == lexema_type_pipe)
            is_pipe = 1;
        lexema_chain = lexema_chain->next;
    }
    return is_pipe;
}

static char** lexema_chain_2_argv(t_list_lexema *lexema_chain)
{
    char** args;
    int i;

    i = ft_lstsize((t_list *)lexema_chain);
    args = (char **)(malloc(sizeof(char *) * (i + 1)));
    i = 0;
    while (lexema_chain)
    {
        args[i] = lexema_chain->lexema->string;
        i++;
        lexema_chain = lexema_chain->next;
    }
    args[i] = NULL;
    return args;
}

static char** list_env_2_env(t_list_env *env_list)
{
    char** env;
    int i;
    char *tmp;

    i = ft_lstsize((t_list *)env_list);
    env = (char **)(malloc(sizeof(char *) * (i + 1)));
    i = 0;
    while (env_list)
    {
        tmp = ft_strjoin("=", env_list->env->value);
        env[i] = ft_strjoin(env_list->env->key, tmp);
        free(tmp);
        i++;
        env_list = env_list->next;
    }
    env[i] = NULL;
    return env;
}

static t_list_env* env_2_list_env(char **env)
{

}

static int exec_lexema_chain_one_command(t_list_lexema *lexema_chain, t_list_env *envs)
{
    char *command_name;
    char **args;
    char **env;
    int res;


    command_name = find_path(lexema_chain->lexema->string, (t_list *)envs);
    if (!command_name)
    {
        error_no_cmd(command_name);
        exit(-1) ;
    }
    args = lexema_chain_2_argv(lexema_chain);
    env = list_env_2_env(envs);

    if ((res = execve(command_name, args, env)) < 0)
    {
        ft_putstr_fd("error: cannot execute ", STDERR_FILENO);
        ft_putstr_fd(command_name, STDERR_FILENO);
        ft_putstr_fd("\n", STDERR_FILENO);
    }
    free(command_name);
    free(args);
    return (res);
}

static int exec_lexema_chain_pipe(t_list_lexema *lexema_chain, t_list_env *envs)
{
    t_list_lexema *one_command_lexemas;
    int		    file_pipes[2];
    pid_t		pid[2];
    int res[2];
    int status[2];

    one_command_lexemas = get_next_lexema_chain(&lexema_chain, lexema_type_pipe);

    if(pipe(file_pipes) < 0) {
        ft_putstr_fd("Pipe could not be initialized\n", STDERR_FILENO);
        exit(9);
    }
     // Программа создает канал с помощью двух файловых дескрипторов из массива file_pipes[].
    // Далее она записывает данные в канал, используя файловый дескриптор file_pipes[1], и считывает их обратно из file_pipes[0].
    pid[0] = fork(); // Когда программа создает новый процесс с помощью вызова fork,
    // уже открытые к этому моменту файловые дескрипторы так и остаются открытыми.
    // Создав канал в исходном процессе и затем сформировав с помощью fork новый процесс,
    // вы сможете передать данные из одного процесса в другой через канал. Cм. картинку pipe.jpg!
    // Процесс-родитель получает идентификатор (PID) потомка. Если это значение будет отрицательным, следовательно при порождении процесса произошла ошибка.
    // Процесс-потомок получает в качестве кода возврата значение 0, если вызов fork() оказался успешным.
    if (pid[0] < 0)
    {
        ft_putstr_fd("Could not fork\n", STDERR_FILENO);
        exit(10);
    }

    if (pid[0] == 0) {
        close(file_pipes[0]);
        dup2(file_pipes[1], STDOUT_FILENO);
        close(file_pipes[1]);

        if((res[0] = exec_lexema_chain_one_command(one_command_lexemas, envs)) < 0)
        {
            ft_putstr_fd("Error: ошибка выполнения команды\n", STDERR_FILENO);
            parser_debug_print_lexema_list(one_command_lexemas);
        }
        exit(res[0]);
    }
    else
    {
        waitpid(pid[0], &(status[0]), 0);
        if (WIFEXITED(status[0]))
            res[0] = WEXITSTATUS(status[0]);
        close(file_pipes[1]);
        pid[1] = fork();
        if (pid[1] < 0)
        {
            ft_putstr_fd("Could not fork\n", STDERR_FILENO);
            exit(10);
        }
        if (pid[1] == 0) {
            close(file_pipes[1]);
            dup2(file_pipes[0], STDIN_FILENO);
            close(file_pipes[0]);

            if((res[1] = eval_lexema_chain(lexema_chain, envs)) < 0)
            {
                ft_putstr_fd("Error: ошибка выполнения команды\n", STDERR_FILENO);
                parser_debug_print_lexema_list(lexema_chain);
            }
            exit(res[1]);
        }
        else
        {

            waitpid(pid[1], &(status[1]), 0);
            if (WIFEXITED(status[1]))
                res[1] = WEXITSTATUS(status[1]);
            else
                res[1] = -1;
            return (res[1]);
        }
    }
}


static int exec_one_command(t_list_lexema *one_command_lexemas, t_list_env *envs)
{
    int		    file_pipes[2];
    pid_t		pid;
    int res;
    int status;


    if(pipe(file_pipes) < 0) {
        ft_putstr_fd("Pipe could not be initialized\n", STDERR_FILENO);
        exit(9);
    }
    // Программа создает канал с помощью двух файловых дескрипторов из массива file_pipes[].
    // Далее она записывает данные в канал, используя файловый дескриптор file_pipes[1], и считывает их обратно из file_pipes[0].
    pid = fork(); // Когда программа создает новый процесс с помощью вызова fork,
    // уже открытые к этому моменту файловые дескрипторы так и остаются открытыми.
    // Создав канал в исходном процессе и затем сформировав с помощью fork новый процесс,
    // вы сможете передать данные из одного процесса в другой через канал. Cм. картинку pipe.jpg!
    // Процесс-родитель получает идентификатор (PID) потомка. Если это значение будет отрицательным, следовательно при порождении процесса произошла ошибка.
    // Процесс-потомок получает в качестве кода возврата значение 0, если вызов fork() оказался успешным.
    if (pid < 0)
    {
        ft_putstr_fd("Could not fork\n", STDERR_FILENO);
        exit(10);
    }

    if (pid == 0) {

        if((res = exec_lexema_chain_one_command(one_command_lexemas, envs)) < 0)
        {
            ft_putstr_fd("Error: ошибка выполнения команды\n", STDERR_FILENO);
            parser_debug_print_lexema_list(one_command_lexemas);
        }
        exit(res);
    }
    else
    {
        waitpid(pid, &(status), 0);
        if (WIFEXITED(status))
            res = WEXITSTATUS(status);
        else
            res = -1;
        return (res);
    }
}

int eval_lexema_chain(t_list_lexema *lexema_chain, t_list_env *envs)
{
    ft_putstr_fd("«eval_lexema_chain.start.*****************************»\n", STDERR_FILENO);
    parser_debug_print_lexema_list(lexema_chain);

    if(is_pipe_in_lexema_chain(lexema_chain))
    {
        return exec_lexema_chain_pipe(lexema_chain, envs);
    }
    else
    {
        return exec_one_command(lexema_chain, envs);
    }
    ft_putstr_fd("«eval_lexema_chain.stop. =============================»\n", STDERR_FILENO);
    ft_putstr_fd("\n", STDERR_FILENO);
}

int parser(char *commandline, int argc, char **argv, t_list_env	*envs)
{
    t_list_lexema *lexema_list;
    t_list_lexema *lexema_chain;
    int res;

    t_lexema *lexema;
    int i = 0;

    lexema_list = get_lexema_list(commandline);

    ft_putstr_fd("«", STDERR_FILENO);
    ft_putstr_fd(commandline, STDERR_FILENO);
    ft_putstr_fd("»\n", STDERR_FILENO);
    parser_debug_print_lexema_list(lexema_list);

    check_marker_syntaxis(lexema_list);

    while ((lexema_chain = get_next_lexema_chain(&lexema_list, lexema_type_semicolon)))
    {
        eval_vars_and_unescape_$_in_lexema_chain(lexema_chain, argc, argv, envs);
        res = eval_lexema_chain((t_list_lexema *)lexema_chain, envs);
    }
    return res;
}