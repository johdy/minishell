#include "minishell.h"

void	add_back_normal_word(char* start, int size, t_list **lex)
{
	char *token;

	token = malloc(size + 2);
	token[0] = ':';
	ft_strlcpy(token + 1, start, size + 1);
	ft_lstadd_back(lex, ft_lstnew(token));
}

void	deal_word(char *line, int *head_ptr, t_list **lex)
{
	int end_word;
	int size;
	int head;
	char *token;

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
	add_back_normal_word(line + head, size, lex);
	(*head_ptr) += size;
	return ;
}

void	get_lex(char *line, t_list **lex)
{
	int head;
	int quotes[2];

	head = 0;
	quotes[0] = 0;
	quotes[1] = 0;
	while (head < ft_strlen(line))
	{
		if (quotes[0] || quotes[1])
			deal_quotes(line, &head, quotes, lex);
		else if (line[head] == 39)
			quotes[0] = 1;
		else if (line[head] == 34)
			quotes[1] = 1;
		else if(line[head] == '<' || line[head] == '>')
			deal_cmp(line, &head, lex);
		else if (line[head] == '|' || line[head] == ';')
			deal_pipe_sc(line, &head, lex);
		else if (line[head] != ' ' && line[head] != '	')
			deal_word(line, &head, lex);
		else
			head++;
	}
	ft_lstadd_back(lex, ft_lstnew(ft_strdup("END")));
	free(line);
}