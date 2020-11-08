/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_redirects_close.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 15:49:46 by kallard           #+#    #+#             */
/*   Updated: 2020/11/08 15:49:47 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_REDIRECTS_CLOSE_H
# define T_REDIRECTS_CLOSE_H

# include "../minishell.h"

typedef struct		s_command
{
	t_list_lexema	*command_with_args;
	int				stdout_fd;
	int				stdin_fd;
}					t_command;

t_command			*t_command_init();
void				t_command_free(t_command *command);

#endif
