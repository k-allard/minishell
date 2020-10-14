/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 22:38:29 by kallard           #+#    #+#             */
/*   Updated: 2020/10/15 00:13:27 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>

typedef struct			s_var
{
	char				*name;
	char				*value;
	int					is_env;
}						t_var;

typedef struct			s_lexer
{
    //...
	char				*input;
	t_list				*env_list;
}						t_lexer;



void        init_lexer(t_lexer *lex, char *input, t_list *env_list);

#endif
