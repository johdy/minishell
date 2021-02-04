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

void		crct_cmd(t_command *cmd, char **ms_e, t_command **cmds, char **path)
{
	t_command *cmd2;

	lookfor_env(cmd, ms_e, cmds, path);
	stick_words(cmd, cmds, ms_e, path);
	cmd2 = cmd->next;
	while (cmd2 && is_redirection_cmd(cmd->end_command))
	{
		lookfor_env(cmd2, ms_e, cmds, path);
		stick_words(cmd, cmds, ms_e, path);
		cmd2 = cmd2->next;
	}
	g_sig.ret = 0;
}
