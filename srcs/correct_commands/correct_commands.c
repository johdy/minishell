/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correct_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdyer <jdyer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 11:00:28 by jdyer             #+#    #+#             */
/*   Updated: 2021/02/02 11:00:29 by jdyer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*suppress_cmd(t_command *cmd, t_command *prev)
{
	t_command	*cache;
	int			i;

	i = 0;
	cache = cmd->next;
	free(prev->end_command);
	prev->end_command = ft_strdup(cmd->end_command);
	while (cmd->words[i])
		free(cmd->words[i++]);
	free(cmd->words);
	free(cmd->end_command);
	free(cmd->quotes);
	free(cmd->stickits);
	free(prev->next);
	prev->next = cache;
	return (prev);
}

char		**copy_previous(t_command *cmd, t_command *cmd2, int *i)
{
	char	**new_w_tb;
	int		e;

	e = 0;
	if (!(new_w_tb = malloc(sizeof(char*) * (cmd->size + cmd2->size))))
		return (0);
	while (cmd->words[e])
	{
		if (!(new_w_tb[e] = ft_strdup(cmd->words[e])))
		{
			free_enomem_table(new_w_tb, e + 1);
			return (0);
		}
		free(cmd->words[e++]);
	}
	*i = e;
	return (new_w_tb);
}

int			correct_multiple_arg_redir(t_command *cmd, t_command *cmd2)
{
	char	**new_w_tb;
	int		j;
	int		i;

	j = 1;
	if (!(new_w_tb = copy_previous(cmd, cmd2, &i)))
		return (0);
	while (cmd2->words[j])
	{
		if (!(new_w_tb[i + j - 1] = ft_strdup(cmd2->words[j])))
		{
			free(cmd->words);
			cmd->words = new_w_tb;
			return (0);
		}
		free(ft_strdup(cmd2->words[j]));
		cmd->size++;
		j++;
	}
	new_w_tb[i + j - 1] = NULL;
	free(cmd->words);
	cmd->words = new_w_tb;
	return (1);
}

void		crct_cmd(t_command *cmd, char **ms_e, t_command **cmds, char **path)
{
	t_command *cmd2;

	lookfor_env(cmd, ms_e, cmds, path);
	stick_words(cmd, cmds, ms_e, path);
	cmd2 = cmd->next;
	while (cmd2 && is_redirection_cmd(cmd->end_command))
	{
		lookfor_env(cmd2, ms_e, cmds, path);
		stick_words(cmd2, cmds, ms_e, path);
		if (cmd2->size > 1)
		{
			if (!(correct_multiple_arg_redir(cmd, cmd2)))
			{
				clean_path(path);
				ft_failed_malloc(ms_e, cmds, 0, 0);
			}
		}
		cmd2 = cmd2->next;
	}
}
