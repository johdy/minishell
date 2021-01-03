/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdyer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 20:45:18 by jdyer             #+#    #+#             */
/*   Updated: 2020/02/04 20:45:19 by jdyer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strilen(char *str)
{
	int i;

	i = 0;
	while (str && str[i] != '\0')
		i++;
	return (i);
}

int		get_chariot(char *str)
{
	int i;

	i = 0;
	while (str && str[i] && str[i] != '\n')
		i++;
	return (i);
}

char	*f_strcpy(char *src, int beg, int end)
{
	char	*dst;
	int		i;

	i = 0;
	if (beg > end)
		return (NULL);
	if (!(dst = malloc(sizeof(char) * (end - beg + 1))))
		return (NULL);
	while (i < end - beg)
	{
		dst[i] = src[beg + i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*f_strcat(char **str1, char *str2, int nb)
{
	char	*ret;
	int		size;
	int		i;

	size = ft_strilen(*str1) + nb;
	i = 0;
	ret = malloc(sizeof(char) * (size + 1));
	while (i < ft_strilen(*str1))
	{
		ret[i] = *(*str1 + i);
		i++;
	}
	while (i < ft_strilen(*str1) + nb)
	{
		ret[i] = str2[i - ft_strilen(*str1)];
		i++;
	}
	ret[i] = '\0';
	free(*str1);
	return (ret);
}
