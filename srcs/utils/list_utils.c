#include "minishell.h"

int		ft_xlstnew_dup(t_list **elem, char *content)
{
	char *elem_dup;

	if (!(elem_dup = ft_strdup(content)))
		return (0);
	if (!(*elem = ft_lstnew(elem_dup)))
	{
		free(elem_dup);
		return (0);
	}
	return (1);
}

int		ft_xlstadd_back_new(t_list **lex, char *content)
{
	t_list *elem;

	if (!(ft_xlstnew_dup(&elem, content)))
		return (0);
	ft_lstadd_back(lex, elem);
	return (1);
}
