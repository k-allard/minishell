/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 15:08:08 by kallard           #+#    #+#             */
/*   Updated: 2020/09/05 15:10:05 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		del_node(t_gnl **head, int fd)
{
	t_gnl *prev;
	t_gnl *tmp;

	tmp = *head;
	if (tmp->fd == fd)
	{
		*head = tmp->next;
		free(tmp);
		return ;
	}
	while (tmp->fd != fd)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	prev->next = tmp->next;
	free(tmp);
}

static t_gnl	*new_node(int fd, char **line)
{
	t_gnl *new;

	new = (t_gnl*)malloc(sizeof(t_gnl));
	*line = ft_strdup("");
	if (!new || !(*line))
		return (NULL);
	new->fd = fd;
	new->remainder = NULL;
	new->next = NULL;
	return (new);
}

static int		check_rem(char **remainder, char **line)
{
	char *p_n;

	p_n = NULL;
	if (*remainder)
	{
		if ((p_n = locate_n(*remainder)))
		{
			*p_n = '\0';
			if (!(*line = ft_strdup(*remainder)))
				return (-1);
			ft_strcpy(*remainder, ++p_n);
			return (1);
		}
		else
		{
			if (!(*line = ft_strdup(*remainder)))
				return (-1);
			free(*remainder);
			*remainder = NULL;
			return (2);
		}
	}
	return (0);
}

static int		get_line(int fd, char **line, char **rem, char *buf)
{
	int		was_read;
	char	*p_n;
	char	*tmp;
	int		n_get;

	if (((n_get = check_rem(rem, line)) == -1) || (read(fd, buf, 0) < 0))
		return (-1);
	while (n_get != 1 && (was_read = read(fd, buf, BUF_SIZE)))
	{
		(buf)[was_read] = '\0';
		if ((p_n = locate_n(buf)))
		{
			*p_n = '\0';
			if (!(*rem = ft_strdup(++p_n)))
				return (-1);
			n_get = 1;
		}
		tmp = *line;
		if (!(*line = ft_strjoin(*line, buf)) || was_read < 0)
			return (-1);
		free(tmp);
	}
	return (n_get == 1) ? 1 : 0;
}

int				get_next_line(int fd, char **line)
{
	static t_gnl	*head;
	t_gnl			*tmp;
	int				gnl;
	char			*buf;

	if (fd < 0 || !line || BUF_SIZE < 1)
		return (-1);
	if (!head && (!(head = new_node(fd, line))))
		return (-1);
	tmp = head;
	while (tmp->fd != fd)
	{
		if ((tmp->next == NULL) && (!(tmp->next = new_node(fd, line))))
			return (-1);
		tmp = tmp->next;
	}
	if (!(buf = malloc(sizeof(*buf) * (BUF_SIZE + 1))))
		return (-1);
	gnl = get_line(tmp->fd, line, &(tmp->remainder), buf);
	if (gnl == 0)
		del_node(&head, tmp->fd);
	free(buf);
	return (gnl);
}
