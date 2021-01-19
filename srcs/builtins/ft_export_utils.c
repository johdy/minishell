#include "minishell.h"

int		check_export(char *str, int i)
{
	if (i == 0)
		return (-1);
	if (i == ft_strlen(str))
		return (0);
	if (i == ft_strlen(str) - 1)
		return (1);
	if ((str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'A' &&str[0] <= 'Z')  || str[0] == '_')
		return (1);
	return (-1);
}

int		deal_wrong_export(char *str, int i, int j)
{
	int err_nb;

	err_nb = check_export(str, i);
	if (err_nb == -1)
	{
		ft_putstr_fd("export: `", 1);
		ft_putstr_fd(str, 1);
		ft_putstr_fd("': not a valid identifier\n", 1);
	}
	return (j + 1);
}

void	append_env(char *str, char ***ms_environ)
{
	int i;
	char **env;
	char **new_env;

	env = *ms_environ;
	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char*) * (i + 2));
	i = -1;
	while (env[++i])
		new_env[i] = ft_strdup(env[i]);
	new_env[i] = ft_strdup(str);
	new_env[i + 1] = NULL;
	clean_path(env);
	*ms_environ = new_env;
}