#include "minishell.h"

int		*get_quotes_nb(t_list *first, int size)
{
	int i;
	int *ret;

	if (!(ret = malloc(sizeof(int) * (size + 1))))
		return (NULL);
	i = 0;
	while (!is_end_command((char *)first->content))
	{
		if (!ft_strcmp((char*)first->content, "QUOTE"))
		{
			ret[i++] = 1;
			first = first->next->next;
		}
		else if (!ft_strcmp((char*)first->content, "DQUOTE"))
		{
			ret[i++] = 0;
			first = first->next->next;
		}
		else if (ft_strcmp((char*)first->content, "STICKIT"))
			ret[i++] = 0;
		first = first->next;
	}
	ret[i] = -1;
	return (ret);
}

int		*get_stickits_nb(t_list *first, int size)
{
	int i;
	int *ret;

	if (!(ret = malloc(sizeof(int) * (size + 1))))
		return (NULL);
	i = 0;
	while (!is_end_command((char *)first->content))
	{
		if (is_q_dq_st((char*)first->content, 1, 1, 0))
		{
			ret[i++] = 0;
			first = first->next->next;
		}
		else if (!ft_strcmp((char*)first->content, "STICKIT"))
			ret[i - 1] = 1;
		else
			ret[i++] = 0;
		first = first->next;
	}
	ret[i] = -1;
	return (ret);
}
