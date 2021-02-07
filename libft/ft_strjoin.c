/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdyer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 19:20:40 by jdyer             #+#    #+#             */
/*   Updated: 2019/11/11 19:39:24 by jdyer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	int		size1;
	int		size2;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && s2)
		return (ft_strdup(s2));
	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	ret = malloc(sizeof(*s1) * (size1 + size2 + 1));
	if (ret == NULL)
		return (NULL);
	ft_strlcpy(ret, s1, size1 + 1);
	ft_strlcat(ret, s2, size1 + size2 + 1);
	return (ret);
}
