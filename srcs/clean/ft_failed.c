/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_failed.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdyer <jdyer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 11:00:18 by jdyer             #+#    #+#             */
/*   Updated: 2021/02/02 11:00:20 by jdyer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_failed_malloc(char **ms_e, t_command **cmds, t_list **lex, void *str)
{
	if (ms_e)
		clean_path(ms_e);
	if (cmds)
		clean_commands(cmds);
	if (lex)
		ft_lstclear(lex, &free);
	if (str)
		free(str);
	ft_putstr_fd("minishell: malloc failiure. exiting\n", 1);
	system("leaks a.out");
	exit(12);
}

void	ft_failed_what(char **ms_e, t_command **cmds, void *str, int id)
{
	if (ms_e)
		clean_path(ms_e);
	if (cmds)
		clean_commands(cmds);
	if (str)
		free(str);
	if (id == -1)
		ft_putstr_fd("minishell: fork failiure. exiting\n", 1);
	if (id == -12)
		ft_putstr_fd("minishell: malloc failiure. exiting\n", 1);
	system("leaks a.out");
	exit(12);
}
