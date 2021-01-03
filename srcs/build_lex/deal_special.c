#include "minishell.h"

void	deal_pipe_sc(char *line, int *head_ptr, t_list **lex)
{
	int head;

	head = *head_ptr;	
	if (line[head] == '|')
		ft_lstadd_back(lex, ft_lstnew(ft_strdup("PIPE")));
	else
		ft_lstadd_back(lex, ft_lstnew(ft_strdup("SC")));
	(*head_ptr)++;
	return ;
}

void	deal_cmp(char *line, int *head_ptr, t_list **lex)
{
	int head;

	head = *head_ptr;
	if (line[head] == '<')
		ft_lstadd_back(lex, ft_lstnew(ft_strdup("LOWER")));
	else if (line[head] == '>' && line[head + 1] != '>')
		ft_lstadd_back(lex, ft_lstnew(ft_strdup("GREATER")));
	(*head_ptr)++;
	if (line[head + 1] != '>')
		return ;
	ft_lstadd_back(lex, ft_lstnew(ft_strdup("DGREATER")));
	(*head_ptr)++;
	return ;
}

void	add_quote_token(int *quotes, t_list **lex)
{
	if (quotes[0])
		ft_lstadd_back(lex, ft_lstnew(ft_strdup("QUOTE")));
	if (quotes[1])
		ft_lstadd_back(lex, ft_lstnew(ft_strdup("DQUOTE")));
}

void	deal_quotes(char *line, int *head_ptr, int *quotes, t_list **lex)
{
	int head;
	int size;
	char *token;

	if (*head_ptr != 0 && line[*head_ptr - 1] != ' ' && line[*head_ptr - 1] != '	' && !is_end_command(line + *head_ptr - 1))
		ft_lstadd_back(lex, ft_lstnew(ft_strdup("STICKIT")));
	add_quote_token(quotes, lex);
	size = 0;
	head = *head_ptr + 1;
	while (quotes[0] && line[head + size] != 39 && line[head + size])
		size++;
	while (quotes[1] && line[head + size] != 34 && line[head + size])
		size++;
	add_back_normal_word(line + head, size, lex);
	add_quote_token(quotes, lex);
	(*head_ptr) += size + 2;
	if (line[*head_ptr] != ' ' && line[*head_ptr] != '	' && line[*head_ptr] != '\0')
		ft_lstadd_back(lex, ft_lstnew(ft_strdup("STICKIT")));
	quotes[0] = 0;
	quotes[1] = 0;		
	return ;
}
