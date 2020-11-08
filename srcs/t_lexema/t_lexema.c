/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_lexema.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 01:29:36 by cwindom           #+#    #+#             */
/*   Updated: 2020/11/08 16:46:27 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Memory allocation and initialization of the new lexema element
** Returns NULL if the memory was not allocated, and t_lexema if it was
*/

t_lexema	*t_lexema_init(void)
{
	t_lexema *lexema;

	lexema = (t_lexema *)malloc(sizeof(t_lexema));
	if (lexema != NULL)
	{
		lexema->lexema_type = lexema_type_default;
		lexema->has_space_before = 0;
		lexema->string = (char *)malloc(sizeof(char ));
		if (lexema->string != NULL)
			lexema->string[0] = '\0';
	}
	return (lexema);
}
