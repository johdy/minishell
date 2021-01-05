#include "minishell.h"

int		stickem(t_command *cmd, int i)
{
	char *conc;
	int j;
	int conc_size;

	j = 1;
	conc_size = ft_strlen(cmd->words[i]) + ft_strlen(cmd->words[i + j]) + 1;
	conc = malloc(conc_size);
	ft_memcpy(conc, cmd->words[i], ft_strlen(cmd->words[i]));
	ft_strlcpy(conc + ft_strlen(cmd->words[i]), cmd->words[i + j], ft_strlen(cmd->words[i + j]) + 1);
	free(cmd->words[i]);
	cmd->words[i] = conc;
	while (cmd->words[i + j + 1])
	{
		free(cmd->words[i + j]);
		cmd->words[i + j] = ft_strdup(cmd->words[i + j + 1]);
		j++;
	}
	free(cmd->words[i + j]);
	free(cmd->words[i + j + 1]);
	cmd->words[i + j] = NULL;
	cmd->size--;
	return (1);
}

void	stick_words(t_command *cmd)
{
	int i;
	int offset;

	offset = 0;
	i = 0;
	while (cmd->stickits[i] != -1)
	{
		if (cmd->stickits[i] && cmd->stickits[i + 1] != -1)
			offset += stickem(cmd, i - offset);
		i++;
	}
}