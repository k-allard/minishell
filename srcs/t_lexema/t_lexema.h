/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_lexema.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 13:27:12 by kallard           #+#    #+#             */
/*   Updated: 2020/11/08 13:29:37 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_LEXEMA_H
# define T_LEXEMA_H

typedef enum		e_lexema_type
{
	lexema_type_default = 0,
	lexema_type_simple_word,
	lexema_type_double_q,
	lexema_type_single_q,
	lexema_type_semicolon,
	lexema_type_redirect_to_append,
	lexema_type_redirect_to,
	lexema_type_redirect_from,
	lexema_type_pipe
}					t_lexema_type;

typedef struct		s_lexema
{
	char			*string;
	int				has_space_before;
	t_lexema_type	lexema_type;
}					t_lexema;

t_lexema			*t_lexema_init();
void				t_lexema_free_void(void *content);

#endif
