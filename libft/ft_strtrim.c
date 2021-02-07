/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdyer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 19:24:34 by jdyer             #+#    #+#             */
/*   Updated: 2019/11/26 20:43:42 by jdyer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		isset(char c, char const *set)
{
	int i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	beg;
	size_t	end;
	size_t	len;
	char	*ret;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	beg = 0;
	end = 0;
	len = ft_strlen(s1);
	while (isset(s1[beg], set) == 1)
		beg++;
	if (beg == len)
		return (ft_strdup(""));
	while (isset(s1[len - end - 1], set) == 1)
		end++;
	if (!(ret = malloc(sizeof(char) * (len - end - beg + 1))))
		return (NULL);
	ft_strlcpy(ret, s1 + beg, len - end - beg + 1);
	return (ret);
}
