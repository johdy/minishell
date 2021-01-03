#include "minishell.h"

int		is_end_command(char *token)
{
	if(ft_strcmp(token, "PIPE") == 0)
		return (1);
	if(ft_strcmp(token, "SC") == 0)
		return (1);
	if(ft_strcmp(token, "GREATER") == 0)
		return (1);
	if(ft_strcmp(token, "DGREATER") == 0)
		return (1);
	if(ft_strcmp(token, "LOWER") == 0)
		return (1);
	if(ft_strcmp(token, "END") == 0)
		return (1);
	return (0);
}

int		is_redirection_cmd(char *token)
{
	if(ft_strcmp(token, "GREATER") == 0)
		return (1);
	if(ft_strcmp(token, "DGREATER") == 0)
		return (1);
	if(ft_strcmp(token, "LOWER") == 0)
		return (1);
	return (0);
}