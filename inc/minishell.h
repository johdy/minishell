/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdyer <jdyer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 10:58:06 by jdyer             #+#    #+#             */
/*   Updated: 2021/02/02 10:58:08 by jdyer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "get_next_line.h"
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <sys/errno.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>

typedef struct			s_command
{
	int					*stickits;
	int					*quotes;
	char				**words;
	void				*end_command;
	int					size;
	int					old_stdin;
	int					old_stdout;
	int					out;
	int					prev_out;
	int					nb_malloc;
	int					abort;
	int					error_exit;
	struct s_command	*next;
}						t_command;

typedef	struct 			s_sig
{
	pid_t				fork;
	int					ret;	
}						t_sig;

int						*execute_cmd(t_command *cmd, char ***ms_environ,
						int *old_stds, t_command **commands);

/*
**Get_bien_path_env
*/
char					**get_path(char **ms_environ, t_command **commands);
char					*get_bin(char *cmd, char **path, char **ms_environ,
						t_command **commands);
char					**init_env(char **ebv);
char					**ft_split_path(char *str, char c);

/*
**Get_lex
*/
void					get_lex(char *line, t_list **lex, char **ms_environ);
int						deal_quotes(char *line, int *head_ptr,
						int *quotes, t_list **lex);
int						deal_cmp(char *line, int *head_ptr, t_list **lex);
int						deal_pipe_sc(char *line, int *head_ptr, t_list **lex);
int						add_back_normal_word(char *start, int size,
						t_list **lex);

/*
**Get_commands
*/
int						get_commands(t_list *lex, t_command **commands,
						char **ms_environ);
int						*get_stickits_nb(t_list *first, int size);
int						*get_quotes_nb(t_list *first, int size);
int						is_q_dq_st(char *tok, int quote, int dquote,
						int stickit);
/*
**Redirections
*/
int						*how_to_open(char *redir, char *file, int *fd_open);
t_command				*deal_redirection(int *pipefd, t_command *cmd,
						int *fd_open);
int						*get_fd_redir(int *fd_open, t_command *cmd);
int						clean_op_fd(int *fd_open, int ret);
int						exec_builtin(t_command *cmd, char ***ms_environ,
						int *pipefd, char *bin);

/*
**Builtins
*/
void					ft_echo(t_command *cmd);
int						ft_cd(t_command *cmd, char **ms_environ);
int						ft_pwd(t_command *cmd);
void					ft_exit(t_command *cmd, char **ms_environ,
						int *pipefd, char *bin);
void					ft_env(t_command *cmd, char **ms_environ);
int						ft_unset(t_command *cmd, char **ms_environ);
int						ft_export(t_command *cmd, char ***ms_environ);
int						append_env(char *str, char ***ms_environ);
int						deal_wrong_env_var(char *str, int i, int j,
						t_command *cmd);
int						check_env_var(char *str, int i);

/*
**Correct
*/
void					crct_cmd(t_command *cmd, char **ms_environ,
						t_command **commands, char **path);
void					stick_words(t_command *cmd, t_command **commands,
						char **ms_environ, char **path);
void					lookfor_env(t_command *cmd, char **ms_environ,
						t_command **commands, char **path);
int						is_envvar_ending(char c);
int						syntax_error_check(t_command **commands, char **ms_e);

/*
**Utils
*/
int						is_end_command(char *token);
int						is_redirection_cmd(char *token);
void					display_commands(t_command **commands);
void					display_lex(t_list **lex);
int						ft_strcmp(char *s1, char *s2);
int						fetch_env(char *id, char **ms_environ, int size);
void					restore_std(int stdin, int stdout);
int						find_eq(char *str);
int						ft_xlstnew_dup(t_list **elem, char *content);
int						ft_xlstadd_back_new(t_list **lex, char *content);
int						check_redir_pipe(t_command *cmd);
void					print_cmd_not_found(t_command *cmd);
void					print_exec_error(t_command *cmd);
void					print_fd_error(t_command *redir, t_command *cmd);
int						print_syntax_error(t_command *cmd, t_command *first);
int						is_builtin(char *cmd);

/*
**Signaux
*/
void					sigc(int mask);
void					sigc_fork(int mask);
void					sigbs(int mask);
void					sigbs_fork(int mask);
void					insert_in_new_input(char **new_input,
						char *reste, char **ms_environ);
char					*deal_ctrld(char *tojoin, char *new_input,
						char **ms_environ);

/*
**Clean
*/
void					clean_commands(t_command **cmds);
void					ft_failed_malloc(char **ms_environ,
						t_command **commands, t_list **lex, void *str);
void					ft_failed_what(char **ms_environ, t_command **commands,
						void *str, int id);
void					clean_commands(t_command **cmds);
void					clean_path(char **path);
char					**free_enomem_table(char **tab, int i);

extern t_sig			g_sig;
#endif
