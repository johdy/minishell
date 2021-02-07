/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdyer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 21:11:16 by jdyer             #+#    #+#             */
/*   Updated: 2019/11/26 21:11:21 by jdyer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *todel;
	t_list *nextlst;

	if (!lst || !(*lst))
		return ;
	todel = *lst;
	nextlst = NULL;
	while (todel)
	{
		nextlst = todel->next;
		del(todel->content);
		free(todel);
		todel = nextlst;
	}
	*lst = NULL;
}
