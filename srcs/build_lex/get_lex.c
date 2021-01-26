#include "minishell.h"

int		add_back_normal_word(char *start, int size, t_list **lex)
{
	char	*token;
	t_list	*new_elem;

	if (!(token = malloc(size + 2)))
		return (0);
	token[0] = ':';
	ft_strlcpy(token + 1, start, size + 1);
	if (!(new_elem = ft_lstnew(token)))
	{
		free(token);
		return (0);
	}
	new_elem->next = NULL;
	ft_lstadd_back(lex, new_elem);
	return (1);
}

int		deal_word(char *line, int *head_ptr, t_list **lex)
{
	int		end_word;
	int		size;
	int		head;
	char	*token;

	head = *head_ptr;
	end_word = 0;
	size = 0;
	while (line[head + size] && !end_word)
	{
		if (line[head + size] == '|' || line[head + size] == ';')
			end_word = 1;
		else if (line[head + size] == '<' || line[head + size] == '>')
			end_word = 1;
		else if (line[head + size] == 39 || line[head + size] == 34)
			end_word = 1;
		else if (line[head + size] == ' ' || line[head + size] == '	')
			end_word = 1;
		else
			size++;
	}
	if (!add_back_normal_word(line + head, size, lex))
		return (0);
	(*head_ptr) += size;
	return (1);
}

int		sail_line(char *line, int *head, int *quotes, t_list **lex)
{
	if (quotes[0] || quotes[1])
		return (deal_quotes(line, head, quotes, lex));
	else if (line[*head] == 39)
		quotes[0] = 1;
	else if (line[*head] == 34)
		quotes[1] = 1;
	else if (line[*head] == '<' || line[*head] == '>')
		return (deal_cmp(line, head, lex));
	else if (line[*head] == '|' || line[*head] == ';')
		return (deal_pipe_sc(line, head, lex));
	else if (line[*head] != ' ' && line[*head] != '	')
		return (deal_word(line, head, lex));
	else
		(*head)++;
	return (1);
}

void	get_lex(char *line, t_list **lex, char **ms_environ)
{
	int		head;
	int		quotes[2];
	t_list	*end;

	head = 0;
	quotes[0] = 0;
	quotes[1] = 0;
	if (!(ft_xlstnew_dup(lex, "START")))
		ft_failed_malloc(ms_environ, 0, 0, line);
	while (head < ft_strlen(line))
	{
		if (!(sail_line(line, &head, quotes, lex)))
			ft_failed_malloc(ms_environ, 0, lex, line);
	}
	if (!(ft_xlstadd_back_new(lex, "END")))
		ft_failed_malloc(ms_environ, 0, lex, line);
	free(line);
}
