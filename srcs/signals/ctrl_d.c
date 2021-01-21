#include "minishell.h"

void	insert_in_new_input(char **new_input, char *reste)
{
	char *tmp;

	tmp = ft_strjoin(reste, *new_input);
	free(reste);
	free(*new_input);
	*new_input = tmp;
}

char	*deal_ctrld(char *tojoin, char *new_input, char **ms_environ)
{
	char *ret;

	ret = NULL;
	if (!ft_strlen(new_input) && !tojoin)
	{
		clean_path(ms_environ);
		free(new_input);
		ft_putstr_fd("exit\n", 1);
		exit(3);
	}
	ft_putstr_fd("  \b\b", 1);
	if (!ft_strlen(new_input))
	{
		free(new_input);
		return (tojoin);
	}
	else if (!tojoin)
	{
		ret = ft_strdup(new_input);
		free(new_input);
		return (ret);
	}
	insert_in_new_input(&new_input, tojoin);
	return (new_input);
}
