/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_special.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdyer <jdyer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 10:58:41 by jdyer             #+#    #+#             */
/*   Updated: 2021/02/02 10:58:44 by jdyer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		deal_pipe_sc(char *line, int *head_ptr, t_list **lex)
{
	int head;

	head = *head_ptr;
	if (line[head] == '|')
	{
		if (!(ft_xlstadd_back_new(lex, "PIPE")))
			return (0);
	}
	else
	{
		if (!(ft_xlstadd_back_new(lex, "SC")))
			return (0);
	}
	(*head_ptr)++;
	return (1);
}

int		deal_cmp(char *line, int *head_ptr, t_list **lex)
{
	int head;

	head = *head_ptr;
	if (line[head] == '<')
	{
		if (!(ft_xlstadd_back_new(lex, "LOWER")))
			return (0);
	}
	else if (line[head] == '>' && line[head + 1] != '>')
	{
		if (!(ft_xlstadd_back_new(lex, "GREATER")))
			return (0);
	}
	(*head_ptr)++;
	if (line[head + 1] != '>' && line[head + 1] != '<')
		return (1);
	if (!(ft_xlstadd_back_new(lex, "DGREATER")))
		return (0);
	(*head_ptr)++;
	return (1);
}

int		add_quote_token(int *quotes, t_list **lex)
{
	if (quotes[0])
	{
		if (!(ft_xlstadd_back_new(lex, "QUOTE")))
			return (0);
	}
	if (quotes[1])
	{
		if (!(ft_xlstadd_back_new(lex, "DQUOTE")))
			return (0);
	}
	return (1);
}

int		put_quoted_word(int *quotes, t_list **lex, int *head, char *line)
{
	int size;

	size = 0;
	while (quotes[0] && line[*head + size] != 39 && line[*head + size])
		size++;
	while (quotes[1] && line[*head + size] != 34 && line[*head + size])
		size++;
	if (!(add_back_normal_word(line + *head, size, lex)))
		return (0);
	if (!(add_quote_token(quotes, lex)))
		return (0);
	(*head) += size + 1;
	if (line[*head] != ' ' && line[*head] != '	' && line[*head] != '\0')
	{
		if (!(ft_xlstadd_back_new(lex, "STICKIT")))
			return (0);
	}
	quotes[0] = 0;
	quotes[1] = 0;
	return (1);
}

int		deal_quotes(char *line, int *head_ptr, int *quotes, t_list **lex)
{
	if (*head_ptr != 0 && line[*head_ptr - 1] != ' ' &&
		line[*head_ptr - 1] != '	')
	{
		if (!(ft_xlstadd_back_new(lex, "STICKIT")))
			return (0);
	}
	if (!(add_quote_token(quotes, lex)))
		return (0);
	(*head_ptr)++;
	if (!put_quoted_word(quotes, lex, head_ptr, line))
		return (0);
	return (1);
}
