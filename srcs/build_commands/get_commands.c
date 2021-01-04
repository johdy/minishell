#include "minishell.h"

int		is_q_dq_st(char *tok, int quote, int dquote, int stickit)
{
	if (quote && !ft_strcmp(tok, "QUOTE"))
		return (1);
	if (dquote && !ft_strcmp(tok, "DQUOTE"))
		return (1);
	if (stickit && !ft_strcmp(tok, "STICKIT"))
		return (1);
	return (0);
}

char	**comm_words_table(t_list *first, int size)
{
	char **ret;
	int i;

	i = 0;
	ret = malloc(sizeof(char*) * (size + 1));
	while (i < size)
	{
		if (!is_q_dq_st((char*)first->content, 1, 1, 1))
			ret[i++] = ft_strdup((char*)first->content + 1);
		first = first->next;
	}
	ret[i] = NULL;
	return (ret);
}

/*int		*fill_quotes(int nb, t_list *first)
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

}*/

t_list	*get_comm_infos(t_command **comm_addr, t_list *lex)
{
	t_command	*comm;
	t_list		*first;

	comm = *comm_addr;
	comm->size = 0;
	first = lex;
	while (!is_end_command((char *)lex->content))
	{
		if (!is_q_dq_st((char*)lex->content, 1, 1, 1))
			comm->size++;
		lex = lex->next;
	}
	comm->stickits = get_stickits_nb(first, comm->size);
	comm->quotes = get_quotes_nb(first, comm->size);
	comm->words = comm_words_table(first, comm->size);
	return (lex);
}

void	get_commands(t_list *lex, t_command **commands)
{
	t_command	*comm;
	t_command	*next_comm;
	int			stickit;
	
	comm = malloc(sizeof(t_command));
	*commands = comm;
	lex = lex->next;
	while (lex)
	{
		lex = get_comm_infos(&comm, lex);
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