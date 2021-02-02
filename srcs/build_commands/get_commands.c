/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdyer <jdyer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:19:38 by jdyer             #+#    #+#             */
/*   Updated: 2021/02/02 10:58:18 by jdyer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	char	**ret;
	int		i;

	i = 0;
	if (!(ret = malloc(sizeof(char*) * (size + 1))))
		return (NULL);
	while (i < size)
	{
		if (!is_q_dq_st((char*)first->content, 1, 1, 1))
		{
			if (!(ret[i++] = ft_strdup((char*)first->content + 1)))
				return (free_enomem_table(ret, i));
		}
		first = first->next;
	}
	ret[i] = NULL;
	return (ret);
}

int		get_comm_infos(t_command **comm_addr, t_list **lex)
{
	t_command	*comm;
	t_list		*first;

	comm = *comm_addr;
	comm->size = 0;
	comm->nb_malloc = 0;
	comm->abort = 0;
	comm->error_exit = 0;
	first = *lex;
	while (!is_end_command((char *)(*lex)->content))
	{
		if (!is_q_dq_st((char*)(*lex)->content, 1, 1, 1))
			comm->size++;
		(*lex) = (*lex)->next;
	}
	if (!(comm->stickits = get_stickits_nb(first, comm->size)))
		return (0);
	comm->nb_malloc++;
	if (!(comm->quotes = get_quotes_nb(first, comm->size)))
		return (0);
	comm->nb_malloc++;
	if (!(comm->words = comm_words_table(first, comm->size)))
		return (0);
	comm->nb_malloc++;
	return (1);
}

int		get_commands(t_list *lex, t_command **commands, char **ms_environ)
{
	t_command	*comm;
	t_command	*next_comm;

	if (!(comm = malloc(sizeof(t_command))))
		ft_failed_malloc(ms_environ, 0, &lex, 0);
	*commands = comm;
	lex = lex->next;
	while (lex)
	{
		comm->next = NULL;
		if (!(get_comm_infos(&comm, &lex)) ||
			!(comm->end_command = ft_strdup((char *)lex->content)))
			return (0);
		comm->nb_malloc++;
		comm->out = 0;
		if (lex->next)
		{
			if (!(next_comm = malloc(sizeof(t_command))))
				return (0);
			comm->next = next_comm;
			comm = comm->next;
		}
		lex = lex->next;
	}
	return (1);
}
