/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bin_and_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdyer <jdyer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 11:01:31 by jdyer             #+#    #+#             */
/*   Updated: 2021/02/02 11:01:33 by jdyer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path(char **ms_environ, t_command **commands)
{
	int		i;
	char	**path;
	char	*first_path;

	i = 0;
	first_path = NULL;
	while (ms_environ[i] && ft_strncmp(ms_environ[i], "PATH=", 5))
		i++;
	if (!ms_environ[i])
		return (NULL);
	if (!(path = ft_split_path(ms_environ[i], ':')))
		ft_failed_malloc(ms_environ, commands, 0, 0);
	if (path[0] && !(first_path =
		ft_substr(path[0], 5, ft_strlen(path[0]) - 5)))
		ft_failed_malloc(ms_environ, commands, 0, 0);
	free(path[0]);
	path[0] = first_path;
	return (path);
}

char	*get_bin(char *cmd, char **path, char **ms_environ, t_command **cmds)
{
	char		*tmp;
	char		*try;
	struct stat	buf;
	int			i;

	i = -1;
	while (path && path[++i])
	{
		if (!(tmp = ft_strjoin(path[i], "/")))
		{
			clean_path(path);
			ft_failed_malloc(ms_environ, cmds, 0, 0);
		}
		try = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!try)
		{
			clean_path(path);
			ft_failed_malloc(ms_environ, cmds, 0, 0);
		}
		if (stat(try, &buf) == 0)
			return (try);
		free(try);
	}
	return (NULL);
}
