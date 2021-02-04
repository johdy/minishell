/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdyer <jdyer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 10:59:08 by jdyer             #+#    #+#             */
/*   Updated: 2021/02/02 10:59:16 by jdyer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_command *cmd, char **ms_environ)
{
	int i;

	i = 0;
	if (cmd->size > 1)
	{
		ft_putstr_fd("env: too many arguments\n", 1);
		cmd->out = 1;
		return ;
	}
	while (ms_environ[i])
	{
		ft_putstr_fd(ms_environ[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

int		delete_env(int i, char **ms_environ)
{
	if (!ms_environ[i])
		return (1);
	while (ms_environ[i])
	{
		free(ms_environ[i]);
		if (ms_environ[i + 1])
		{
			if (!(ms_environ[i] = ft_strdup(ms_environ[i + 1])))
				return (0);
		}
		i++;
	}
	free(ms_environ[i]);
	ms_environ[i - 1] = NULL;
	return (1);
}

int		ft_unset(t_command *cmd, char **ms_environ)
{
	int		i;
	int		j;
	int		match;

	if (cmd->size == 1)
		return (1);
	j = 0;
	while (j < cmd->size - 1)
	{
		match = 0;
		deal_wrong_env_var(cmd->words[1 + j], -2, 0, cmd);
		i = fetch_env(cmd->words[1 + j], ms_environ, 0);
		if (!(delete_env(i, ms_environ)))
			return (0);
		j++;
	}
	return (1);
}
