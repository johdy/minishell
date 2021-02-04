/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdyer <jdyer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 10:59:30 by jdyer             #+#    #+#             */
/*   Updated: 2021/02/02 10:59:31 by jdyer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		free_table(char **new_env, int i)
{
	free_enomem_table(new_env, ++i);
	return (0);
}

int		append_env(char *str, char ***ms_environ)
{
	int		i;
	char	**env;
	char	**new_env;

	env = *ms_environ;
	i = 0;
	while (env[i])
		i++;
	if (!(new_env = malloc(sizeof(char*) * (i + 2))))
		return (0);
	i = -1;
	while (env[++i])
	{
		if (!(new_env[i] = ft_strdup(env[i])))
			return (free_table(new_env, i));
	}
	if (!(new_env[i] = ft_strdup(str)))
		return (free_table(new_env, i));
	new_env[i + 1] = NULL;
	clean_path(env);
	*ms_environ = new_env;
	return (1);
}
