/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdyer <jdyer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 10:59:22 by jdyer             #+#    #+#             */
/*   Updated: 2021/02/02 10:59:23 by jdyer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		*get_ordering(char **ms_environ, int size)
{
	int *ret;
	int i;
	int cache;

	if (!(ret = malloc(sizeof(int) * (size + 1))))
		return (NULL);
	i = -1;
	while (++i < size)
		ret[i] = i;
	ret[i] = -1;
	i = 0;
	while (i < size - 1)
	{
		if (ft_strcmp(ms_environ[ret[i]], ms_environ[ret[i + 1]]) > 0)
		{
			cache = ret[i + 1];
			ret[i + 1] = ret[i];
			ret[i] = cache;
			i = 0;
		}
		else
			i++;
	}
	return (ret);
}

int		display_export(char **ms_environ)
{
	int i;
	int j;
	int *class;
	int c;

	i = 0;
	while (ms_environ[i])
		i++;
	if (!(class = get_ordering(ms_environ, i)))
		return (0);
	j = -1;
	while (++j < i)
	{
		c = 0;
		ft_putstr_fd("declare -x ", 1);
		while (ms_environ[class[j]][c] != '=')
			write(1, ms_environ[class[j]] + c++, 1);
		ft_putstr_fd("=\"", 1);
		c++;
		while (ms_environ[class[j]][c])
			write(1, ms_environ[class[j]] + c++, 1);
		ft_putstr_fd("\"\n", 1);
	}
	free(class);
	return (1);
}

int		ft_export(t_command *cmd, char ***ms_environ)
{
	int		i;
	int		j;
	int		ms_env_pos;
	char	**ms_env_copy;

	if (cmd->size == 1)
		return (display_export(*ms_environ));
	j = 0;
	while (j < cmd->size - 1)
	{
		ms_env_copy = *ms_environ;
		i = find_eq(cmd->words[1 + j]);
		ms_env_pos = fetch_env(cmd->words[1 + j], ms_env_copy, i);
		if (check_env_var(cmd->words[1 + j], i) != 1)
			j = deal_wrong_env_var(cmd->words[1 + j], i, j, cmd);
		else if (ms_env_copy[ms_env_pos])
		{
			free(ms_env_copy[ms_env_pos]);
			if (!(ms_env_copy[ms_env_pos] = ft_strdup(cmd->words[1 + j++])))
				return (0);
		}
		else if (!(append_env(cmd->words[1 + j++], ms_environ)))
			return (0);
	}
	return (1);
}
