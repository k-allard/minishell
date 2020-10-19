
# include <sys/errno.h>
# include <dirent.h> //для DIR

void ft_cd(int argc, char **argv)
{
	DIR		*dir; //Тип, представляющий поток каталога
	char	*path;
    int		er; //можно положить в структуру с ошибками

	er = 0;
	if (argc > 1)
		path = argv[1];
	else
        printf("%s", "Здесь будет какой-то код чтобы попасть в Home");
	if (path == NULL)
		return ;
	dir = opendir(path);
	if (dir != NULL)
	{
		if (chdir(path) < 0)
			er = 1;
		if (closedir(dir) < 0)
			er = 1;
	}
	else
		er = 1;
	if (er)
        printf("%s", "вывести ошибку с помощью strerror(errno)");
}