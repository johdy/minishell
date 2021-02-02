/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdyer <jdyer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 11:01:39 by jdyer             #+#    #+#             */
/*   Updated: 2021/02/02 11:01:40 by jdyer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**init_env(char **env)
{
	char	**ret;
	int		size;
	int		i;

	i = 0;
	size = 0;
	while (env[size])
		size++;
	if (!(ret = malloc(sizeof(char*) * (size + 1))))
		ft_failed_malloc(0, 0, 0, 0);
	while (i < size)
	{
		if (!(ret[i] = ft_strdup(env[i])))
			ft_failed_malloc(ret, 0, 0, 0);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
