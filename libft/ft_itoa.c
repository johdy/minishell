/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdyer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 19:18:49 by jdyer             #+#    #+#             */
/*   Updated: 2019/11/26 20:51:29 by jdyer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		nbdig(int n)
{
	int i;
	int dig;

	dig = 0;
	i = 1;
	while (n / i >= 1)
	{
		dig++;
		if (i < 1000000000)
			i = i * 10;
		else
			break ;
	}
	return (dig);
}

char	*ft_itoa2(int dig, int n, int intmin, int sign)
{
	char *ret;

	ret = malloc(sizeof(char) * (dig + 1));
	if (ret == NULL)
		return (NULL);
	ret[dig] = '\0';
	while (n >= 10)
	{
		ret[dig - 1] = (n % 10) + '0';
		n = n / 10;
		dig--;
	}
	ret[dig - 1] = n + '0';
	if (intmin == 1)
		ret[10]++;
	if (sign == -1)
		ret[0] = '-';
	return (ret);
}

char	*ft_itoa(int n)
{
	int dig;
	int sign;
	int intmin;

	dig = 0;
	intmin = 0;
	sign = 1;
	if (n < 0)
	{
		dig++;
		sign = -1;
		if (n == -2147483648)
		{
			intmin = 1;
			n++;
		}
		n = -n;
	}
	if (n == 0)
		dig = 1;
	dig += nbdig(n);
	return (ft_itoa2(dig, n, intmin, sign));
}
