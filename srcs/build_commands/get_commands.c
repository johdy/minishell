#include "minishell.h"

char	**comm_words_table(t_list *first, int size)
{
	char **ret;
	int i;

	i = 0;
	ret = malloc(sizeof(char*) * (size + 1));
	while (i < size)
	{
		if (ft_strcmp((char*)first->content, "QUOTE") && ft_strcmp((char*)first->content, "DQUOTE") && ft_strcmp((char*)first->content, "STICKIT"))
			ret[i++] = ft_strdup((char*)first->content + 1);
		first = first->next;
	}
	ret[i] = NULL;
	return (ret);
}

int		*fill_quotes(int nb, t_list *first)
{
	int *ret;
	int i;
	int nb_lex;
	int new;

	i = 0;
	nb_lex = 0;
	new = 1;
	ret = malloc(sizeof(int) * (nb + 1));
	while (i < nb)
	{
		if (!ft_strcmp((char*)first->content, "QUOTE") && new)
		{
			ret[i++] = nb_lex;
			new = 0;
		}
		else if (!ft_strcmp((char*)first->content, "QUOTE") && !new)
			new = 1;
		else if (ft_strcmp((char*)first->content, "DQUOTE"))
			nb_lex++;
		first = first->next;
	}
	ret[i] = -1;
	return (ret);

}

int		*get_quotes_nb(t_list *first, int size)
{
	int i;
	int *ret;

	ret = malloc(sizeof(int) * (size + 1));
	i = 0;
	while (!is_end_command((char *)first->content))
	{
		if (!ft_strcmp((char*)first->content, "QUOTE"))
		{
			ret[i++] = 1;
			first = first->next->next->next;
		}
		else if (!ft_strcmp((char*)first->content, "DQUOTE"))
		{
			ret[i++] = 0;
			first = first->next->next->next;
		}
		else if (!ft_strcmp((char*)first->content, "STICKIT"))
			first = first->next;
		else
		{	
			ret[i++] = 0;
			first = first->next;
		}
	}
	ret[i] = -1;
	return (ret);
}

int		*get_stickits_nb(t_list *first, int size)
{
	int i;
	int *ret;

	ret = malloc(sizeof(int) * (size + 1));
	i = 0;
	while (!is_end_command((char *)first->content))
	{
		if (!ft_strcmp((char*)first->content, "QUOTE"))
		{
			ret[i++] = 0;
			first = first->next->next->next;
		}
		else if (!ft_strcmp((char*)first->content, "DQUOTE"))
		{
			ret[i++] = 0;
			first = first->next->next->next;
		}
		else if (!ft_strcmp((char*)first->content, "STICKIT"))
		{
			ret[i - 1] = 1;
			first = first->next;
		}
		else
		{	
			ret[i++] = 0;
			first = first->next;
		}
	}
	ret[i] = -1;
	return (ret);
}

void	get_commands(t_list *lex, t_command **commands)
{
	t_command	*comm;
	t_command	*next_comm;
	t_list		*first;
	int			stickit;
	comm = malloc(sizeof(t_command));
	*commands = comm;
	while (lex)
	{
		comm->size = 0;
		first = lex;
		while (!is_end_command((char *)lex->content))
		{
			if (ft_strcmp((char*)lex->content, "QUOTE") && ft_strcmp((char*)lex->content, "DQUOTE") && ft_strcmp((char*)lex->content, "STICKIT"))
				comm->size++;
			lex = lex->next;
		}
		comm->stickits = get_stickits_nb(first, comm->size);
		comm->quotes = get_quotes_nb(first, comm->size);
		comm->words = comm_words_table(first, comm->size);
		comm->end_command = ft_strdup((char *)lex->content);
		if (lex->next)
		{
			next_comm = malloc(sizeof(t_command));
			comm->next = next_comm;
			comm = comm->next;
		}
		lex = lex->next;
	}
	comm->next = NULL;
}