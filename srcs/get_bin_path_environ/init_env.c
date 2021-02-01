#include "minishell.h"

char		**init_env(void)
{
	char	**ret;
	int		size;
	int		i;

	i = 0;
	size = 0;
	while (environ[size])
		size++;
	if (!(ret = malloc(sizeof(char*) * (size + 1))))
		ft_failed_malloc(0, 0, 0, 0);
	while (i < size)
	{
		if (!(ret[i] = ft_strdup(environ[i])))
			ft_failed_malloc(ret, 0, 0, 0);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
