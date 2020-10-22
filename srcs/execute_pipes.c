/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 22:02:58 by kallard           #+#    #+#             */
/*   Updated: 2020/10/21 22:30:52 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/*
** парсится и сохраняется в структуру левая часть конвейра, правая - остается в лайн
*/

void parse_pipes(char **line, t_pipe *pipe, t_list *envs)
{
	int		i;
	char	*tmp1;
	char	*tmp2;

	i = -1;
	while ((*line)[++i])
	{
		if ((*line)[i] == '|')
		{
			tmp1 = ft_substr(*line, 0, i);
			pipe->left_end = ft_strtrim(tmp1, " ");
			free(tmp1);
			tmp1 = ft_substr(*line, i + 1, ft_strlen(*line) - i);
			tmp2 = ft_strtrim(tmp1, " ");
			free(tmp1);
			*line = tmp2;
			pipe->argv = get_argumentes(pipe->left_end, envs);
			return ;
		}
	}
}

void	execute_left_pipe_end(int file_pipes[2], t_list *envs, char *left_end, t_all all)
{
    dup2(file_pipes[1], STDOUT_FILENO); //int dup2(int oldfd, int newfd) Делает newfd копией oldfd; 
    close(file_pipes[0]);
    close(file_pipes[1]);
    execute_commands(left_end, envs, all);
    exit(EXIT_SUCCESS);
}

void	execute_right_pipe_end(int file_pipes[2], t_list *envs, char *line, t_all all)
{
    dup2(file_pipes[0], STDIN_FILENO);
    close(file_pipes[0]);
    close(file_pipes[1]);
    execute_commands(line, envs, all);
    exit(EXIT_SUCCESS);
}

void execute_pipes(char *line, t_list *envs, t_all all)
{
    int		    file_pipes[2];
	pid_t		pid[2];
	t_pipe	    p;

    parse_pipes(&line, &p, envs);
    pipe(file_pipes); // Программа создает канал с помощью двух файловых дескрипторов из массива file_pipes[]. 
    // Далее она записывает данные в канал, используя файловый дескриптор file_pipes[1], и считывает их обратно из file_pipes[0].
    pid[0] = fork(); // Когда программа создает новый процесс с помощью вызова fork, 
    // уже открытые к этому моменту файловые дескрипторы так и остаются открытыми. 
    // Создав канал в исходном процессе и затем сформировав с помощью fork новый процесс, 
    // вы сможете передать данные из одного процесса в другой через канал. Cм. картинку pipe.jpg!
    // Процесс-родитель получает идентификатор (PID) потомка. Если это значение будет отрицательным, следовательно при порождении процесса произошла ошибка. 
    // Процесс-потомок получает в качестве кода возврата значение 0, если вызов fork() оказался успешным.
    if (pid[0] == 0)
		execute_left_pipe_end(file_pipes, envs, p.left_end, all);     // в структуре p - левая часть конвейра, в лайн - правая
    // можно освободить структуру p
	pid[1] = fork();
	if (pid[1] == 0)
	    execute_right_pipe_end(file_pipes, envs, line, all);
    waitpid(pid[1], NULL, 0);
	waitpid(pid[0], NULL, WNOHANG); //  pid_t waitpid(pid_t pid, int *status, int options); 
    // приостанавливает выполнение текущего процесса до тех пор, пока дочерний процесс, указанный в 
    // параметре pid, не завершит выполнение, или пока не появится сигнал, который либо завершает текущий процесс либо 
    // требует вызвать функцию-обработчик. Если указанный дочерний процесс к моменту вызова функции уже 
    // завершился (так называемый "зомби"), то функция немедленно возвращается. Системные ресурсы, связанные 
    // с дочерним процессом, освобождаются.
    // Второй аргумент представляет собой указатель на целое число. Если в аргументе передается непустой указатель, то по заданному адресу будет записан код завершения дочернего процесса. Если код завершения нас не интересует, то можно просто передать в этом аргументе пустой указатель.
    // Третий аргумент: Опция WNOHANG означает немедленное возвращение управления, если ни один дочерний процесс не завершил выполнение.
}