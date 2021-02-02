/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_dollars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdyer <jdyer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 11:00:35 by jdyer             #+#    #+#             */
/*   Updated: 2021/02/02 11:00:36 by jdyer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		delete_word(t_command *cmd, int i)
{
	int cpt;

	cpt = 0;
	while (cmd->words[i + cpt + 1])
	{
		free(cmd->words[i + cpt]);
		cmd->words[i + cpt] = ft_strdup(cmd->words[i + cpt + 1]);
		cmd->stickits[i + cpt] = cmd->stickits[i + cpt + 1];
		cmd->quotes[i + cpt] = cmd->quotes[i + cpt + 1];
		cpt++;
	}
	free(cmd->words[i + cpt]);
	free(cmd->words[i + cpt + 1]);
	cmd->words[i + cpt] = NULL;
	cmd->stickits[i + cpt] = -1;
	cmd->quotes[i + cpt] = -1;
	cmd->size--;
	return (-1);
}

int		suppress_wrong_env(t_command *cmd, int i, int j)
{
	char	*new_word;
	int		cpt;

	cpt = 0;
	if (j == 0)
		return (delete_word(cmd, i));
	if (!(new_word = ft_substr(cmd->words[i], 0, j)))
		return (-12);
	free(cmd->words[i]);
	cmd->words[i] = new_word;
	return (-1);
}

int		put_ret_nb(t_command *cmd, int i, int j)
{
	char *tocopy;
	char *new_word;

	if (!(tocopy = ft_itoa(cmd->prev_out)))
		return (-12);
	if (!(new_word = malloc(ft_strlen(cmd->words[i]) - 2
		+ ft_strlen(tocopy) + 1)))
	{
		free(tocopy);
		return (-12);
	}
	ft_memcpy(new_word, cmd->words[i], j);
	ft_memcpy(new_word + j, tocopy, ft_strlen(tocopy));
	ft_strlcpy(new_word + j + ft_strlen(tocopy), cmd->words[i] + j + 2,
		ft_strlen(cmd->words[i]) - 2 + 1);
	free(cmd->words[i]);
	free(tocopy);
	cmd->words[i] = new_word;
	return (1);
}

int		replace_env(t_command *cmd, int i, int j, char **ms_e)
{
	int		szw;
	int		w;
	char	*new_word;

	j++;
	szw = 0;
	while (!is_envvar_ending(cmd->words[i][j + szw]) &&
		cmd->words[i][j + szw])
		szw++;
	w = fetch_env(cmd->words[i] + j, ms_e, szw);
	j--;
	if (!ms_e[w] && cmd->words[i][j + 1] != '?')
		return (0);
	else if (!ms_e[w])
		return (put_ret_nb(cmd, i, j));
	if (!(new_word = malloc(ft_strlen(cmd->words[i]) - (szw + 1) +
		ft_strlen(ms_e[w]) - (szw + 1) + 1)))
		return (-12);
	ft_memcpy(new_word, cmd->words[i], j);
	ft_memcpy(new_word + j, ms_e[w] + szw + 1, ft_strlen(ms_e[w]) - (szw + 1));
	ft_strlcpy(new_word + j + ft_strlen(ms_e[w]) - (szw + 1), cmd->words[i] +
		szw + j + 1, ft_strlen(cmd->words[i]) - (szw + 1) + 1);
	free(cmd->words[i]);
	cmd->words[i] = new_word;
	return (1);
}

void	lookfor_env(t_command *cmd, char **ms_e, t_command **cmds, char **path)
{
	int i;
	int j;
	int replace;

	i = -1;
	while (cmd->words[++i])
	{
		j = 0;
		while (j >= 0 && cmd->words[i][j])
		{
			if (cmd->words[i][j] == '$' && !cmd->quotes[i])
			{
				replace = replace_env(cmd, i, j, ms_e);
				if (replace == 0)
					j = suppress_wrong_env(cmd, i--, j);
				if (replace == -12 || j == -12)
				{
					clean_path(path);
					ft_failed_malloc(ms_e, cmds, 0, 0);
				}
				j--;
			}
			j++;
		}
	}
}
