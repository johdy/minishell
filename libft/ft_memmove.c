/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdyer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 16:52:50 by jdyer             #+#    #+#             */
/*   Updated: 2019/11/11 16:52:53 by jdyer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	protectedcpy(unsigned char *dstcpy, unsigned char *srccpy, size_t len)
{
	size_t	i;

	i = len;
	while (i != 0)
	{
		i--;
		dstcpy[i] = srccpy[i];
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char *dstcpy;
	unsigned char *srccpy;

	dstcpy = (unsigned char *)dst;
	srccpy = (unsigned char *)src;
	if (dst == src)
		return (dst);
	if (dstcpy < srccpy)
		ft_memcpy(dst, src, len);
	else
		protectedcpy(dstcpy, srccpy, len);
	return (dst);
}
