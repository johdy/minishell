/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdyer <jdyer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 11:01:23 by jdyer             #+#    #+#             */
/*   Updated: 2021/02/02 11:01:26 by jdyer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		malloc_last_word(char **tab, long int nbw, char *str)
{
	if (nbw != 0)
		tab[nbw - 1] = ft_strdup(str);
	else
		return (0);
	if (!tab[nbw - 1])
	{
		free(tab[nbw - 1]);
		return (0);
	}
	return (1);
}

int		ft_nbw(char *str, char c)
{
	int ret;
	int i;

	if (str == NULL || *str == '\0')
		return (0);
	i = 0;
	ret = 1;
	while (str[i])
	{
		if (str[i] == c)
		{
			while (str[i] == c)
				i++;
			ret++;
		}
		i++;
	}
	return (ret);
}

char	**ft_split_path(char *str, char c)
{
	long int	nbw;
	char		**tab;
	long int	i;

	i = 0;
	nbw = ft_nbw(str, c);
	if (!(tab = malloc(sizeof(char*) * (nbw + 1))))
		return (0);
	if (nbw == 0)
		return (tab);
	while (i + 1 < nbw)
	{
		if (!(tab[i++] = ft_substr(str, 0, ft_strchr(str, c) - str)))
			return (free_enomem_table(tab, i));
		if (!(str = ft_strchr(str, c)))
			return (free_enomem_table(tab, i + 1));
		while (*str == c)
			str++;
	}
	if (!(malloc_last_word(tab, nbw, str)))
		return (free_enomem_table(tab, ++i));
	tab[nbw] = 0;
	return (tab);
}
