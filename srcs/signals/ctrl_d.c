#include "minishell.h"

void	ctrld_exit(char **ms_environ, char *new_input)
{
	clean_path(ms_environ);
	free(new_input);
	ft_putstr_fd("exit\n", 1);
	exit(0);	
}

void	insert_in_new_input(char **new_input, char *reste, char **ms_environ)
{
	char *tmp;

	tmp = ft_strjoin(reste, *new_input);
	free(reste);
	free(*new_input);
	if (tmp == NULL)
		ft_failed_malloc(ms_environ, 0, 0, 0);
	*new_input = tmp;
}

char	*deal_ctrld(char *tojoin, char *new_input, char **ms_environ)
{
	char *ret;

	ret = NULL;
	if (!ft_strlen(new_input) && !tojoin)
		ctrld_exit(ms_environ, new_input);
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
		if (!ret)
			ft_failed_malloc(ms_environ, 0, 0, 0);
		return (ret);
	}
	insert_in_new_input(&new_input, tojoin, ms_environ);
	return (new_input);
}
