/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdyer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 21:15:00 by jdyer             #+#    #+#             */
/*   Updated: 2019/11/26 21:15:05 by jdyer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *ret;
	t_list *cache;

	if (!lst)
		return (NULL);
	if (!(ret = ft_lstnew(f(lst->content))))
		return (NULL);
	cache = ret;
	while (lst)
	{
		if (lst->next)
		{
			ret->next = ft_lstnew(f(lst->next->content));
			if (ret->next == NULL)
			{
				ft_lstclear(&cache, del);
				return (NULL);
			}
			ret = ret->next;
		}
		lst = lst->next;
	}
	return (cache);
}
