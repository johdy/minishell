#include "minishell.h"

int		find_eq(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

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

int		is_envvar_ending(char c)
{
	if (ft_isalnum(c))
		return (0);
	if (c == '_')
		return (0);
	return (1);
}
