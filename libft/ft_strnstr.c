/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdyer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 12:09:45 by jdyer             #+#    #+#             */
/*   Updated: 2019/11/26 21:18:31 by jdyer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *need, size_t len)
{
	size_t	i;
	size_t	size;

	size = ft_strlen(need);
	if (size > len)
		return (NULL);
	i = 0;
	if (hay == NULL || need == NULL)
		return (NULL);
	if (*need == '\0')
		return ((char *)hay);
	while (hay[i] != '\0' && i < len - size + 1)
	{
		if (ft_memcmp(hay + i, need, ft_strlen(need)) == 0)
			return ((char *)&hay[i]);
		i++;
	}
	return (NULL);
}
