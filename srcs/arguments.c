///* ************************************************************************** */
///*                                                                            */
///*                                                        :::      ::::::::   */
///*   arguments.c                                        :+:      :+:    :+:   */
///*                                                    +:+ +:+         +:+     */
///*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
///*                                                +#+#+#+#+#+   +#+           */
///*   Created: 2020/10/23 14:48:17 by kallard           #+#    #+#             */
///*   Updated: 2020/10/25 14:54:53 by kallard          ###   ########.fr       */
///*                                                                            */
///* ************************************************************************** */
//
//#include "minishell.h"
//
///*
//**
//*/
//
//char	**get_argumentes(char *line, t_list *envs)
//{
//	int		i;
//	char	**argv;
//
//	if (!(argv = ft_split(line, ' ')))
//		return (0);
//	i = -1;
//	while (argv[++i])
//	{
//		// if (ft_strlen(argv[i]) > 1 && quote_found(argv[i]))
//		// 	argv[i] = deal_with_quotes(argv[i], envs);
//        if (ft_strlen(argv[i]) > 1 && dollar_found(argv[i]))
//			argv[i] = insert_variable(argv[i], envs);
//	}
//	return (argv);
//}
