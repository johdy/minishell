/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdyer <jdyer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 11:00:11 by jdyer             #+#    #+#             */
/*   Updated: 2021/02/02 11:00:12 by jdyer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**free_enomem_table(char **tab, int i)
{
	i--;
	i--;
	while (i >= 0)
		free(tab[i--]);
	free(tab);
	return (NULL);
}

void	clean_cmd(t_command *cmd)
{
	int i;

	if (cmd->nb_malloc > 0)
		free(cmd->stickits);
	if (cmd->nb_malloc > 1)
		free(cmd->quotes);
	if (cmd->nb_malloc > 2)
	{
		i = 0;
		while (cmd->words[i])
			free(cmd->words[i++]);
		free(cmd->words);
	}
	if (cmd->nb_malloc > 3)
		free(cmd->end_command);
}

void	clean_commands(t_command **cmds)
{
	t_command *cmd;
	t_command *cache;

	cmd = *cmds;
	while (cmd)
	{
		clean_cmd(cmd);
		cache = cmd->next;
		free(cmd);
		cmd = cache;
	}
}

void	clean_path(char **path)
{
	int i;

	i = 0;
	while (path && path[i])
		free(path[i++]);
	if (path)
		free(path);
}
