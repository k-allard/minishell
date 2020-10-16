# minishell

Раздрешенные функции:
malloc, free, write, open, read, close, fork, wait, waitpid, wait3, wait4, signal, kill, exit, getcwd, chdir, stat, lstat, fstat, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, errno

Команды:
- echo - отображает строку теста (с опцией '-n' выводит без завершающего '\n')
- cd - изменяет текущий рабочий каталог (в качестве аргумента принимает абсолютный или относительный адрес; путь является абсолютным, если он начинается с / . В противном случае это относительный путь)
- pwd без опций
- export без опций - выводит имена всех переменных, отмеченных для экспорта в дочерние процессы
- unset без опций - удаляет переменную, фактически - устанавливает ее значение в null
- env без опций и аргументов - выводит список всех переменных окружения
- exit без опций
- ; - разделяет команды
- " ' - двойные кавычки позволяют осуществлять раскрытие переменных в строке команды, в то время, как одинарные кавычки позволяют предотвратить такое раскрытие (except for multiline commands)
- < > “>>” перенаправления (except for file descriptor aggregation)
- | - конвейер - вывод одной команды подается на вход другой
- Environment variables ($ followed by characters)
- $?
- ctrl-C, ctrl-D and ctrl-\

Заметки:
* Про уровни оболочки и переменную $SHLVL https://solutics.ru/linux/kak-i-pochemu-vy-dolzhny-ispolzovat-peremennuyu-shlvl/