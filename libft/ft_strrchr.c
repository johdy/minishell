/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdyer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:59:02 by jdyer             #+#    #+#             */
/*   Updated: 2019/11/11 19:40:13 by jdyer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		cpt;
	char	*cache;

	cpt = 0;
	cache = NULL;
	while (s[cpt] != '\0')
	{
		if (s[cpt] == c)
			cache = (char *)&s[cpt];
		cpt++;
	}
	if (c == '\0')
		cache = (char *)&s[cpt];
	return (cache);
}
