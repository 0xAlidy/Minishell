/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 21:59:37 by alidy             #+#    #+#             */
/*   Updated: 2021/01/27 15:16:20 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define TRUE 1
# define FALSE 0
# include "../libft/include/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# include <limits.h>

typedef struct			s_arg
{
	char				*content;
	struct s_arg		*next;
}						t_arg;

typedef struct			s_env
{
	char				*name;
	char				*content;
	struct s_env		*next;
}						t_env;

typedef struct			s_parse
{
	int					save;
	int					none;
	int					type_output;
	int					in_squote;
	int					in_dquote;
	int					in_dollar;
	int					in_slash;
	char				*content;
	t_env				**env;
}						t_parse;

typedef struct			s_output
{
	char				*content;
	int					type;
	struct s_output		*next;
}						t_output;

typedef struct			s_cmd
{
	t_arg				*args;
	t_output			*output;
	int					pipe;
	struct s_cmd		*next;
}						t_cmd;

typedef struct			s_sct
{
	int					status;
	int					in_pipe;
	int					in_fork;
	char				**args;
	char				*path;
	char				**envp;
	int					saved_stdout;
	int					saved_stdin;
	t_cmd				**saved_cmds;
}						t_sct;

t_cmd					*ms_set_commands(char *line, t_env **env, t_sct *sct);
int						ms_set_command(char *l, int i, t_cmd *cmd, t_env **env);
int						ms_set_content(char *l, int i, t_parse *p, t_cmd *cmd);
int						ms_parse_line(char *l, int i, t_parse *p, t_cmd *cmd);
char					*ms_create_dollar(char *str, int i, t_parse *parse);
void					ms_create_string(char *line, int i, t_parse *parse);
int						ms_parse_arg(char *line, int i, t_parse *parse);
t_parse					ms_init_parse(t_env **env);
t_output				*ms_new_output(char *output, int type);
t_arg					*ms_new_arg(char *arg);
t_cmd					*ms_new_command();
int						ms_free_parse(int res, char *msg, t_parse *parse);
void					ms_add_command(t_cmd **commands, t_cmd *command);
void					ms_add_output(char *output, int type, t_output **lst);
void					ms_add_arg(char *content, t_arg **lst);
int						ms_is_char_printable(int c);
int						ms_check_end(t_parse *parse, char *line, int i);
void					ms_create_space(char *line, int *i, t_parse *parse);
int						ms_handler_slash(char *line, int *i, t_parse *parse);
void					ms_handler_dollar(char *line, int *i, t_parse *parse);
void					ms_handler_quotes(char *line, int *i, t_parse *parse);
t_env					**ms_sort_env(t_env **env);
int						ms_gnl_eof(int fd, char **line);
char					*ms_get_env(char **env, char *key);
t_env					*ms_new_env(char *name, char *content);
void					ms_add_env(char *name, char *content, t_env **lst);
t_env					*ms_set_env(char **tab);
char					*ms_search_env(char *str, t_env **lst);
int						ms_modify_env(t_env **env, char *name, char *content);
char					*ms_current_folder();
t_sct					ms_init_sct();
char					*ms_minitrim(char *str);
int						ms_indexchr(char *s, int c);
void					ms_prompt(t_sct *sct);
void					ms_signal_handler(int type);
void					ms_set_envp(t_sct *sct, t_env **env);
int						ms_set_redirections(t_sct *sct, t_cmd *command);
char					*ms_search_path(t_sct *sct);
int						ms_test_path(char *path, t_sct *sct);
void					ms_transfort_args(t_sct *sct, t_arg **args);
void					ms_exec_simple_command(t_sct *s, t_cmd *cmd, t_env *e);
void					ms_exec_commands(t_sct *sct, t_cmd **cmds, t_env *env);
void					ms_exec_pipe(t_sct *sct, t_cmd **command, t_env *env);
int						ms_handler_builtin(t_sct *sct, t_env *env);
void					ms_exec_fork(t_sct *sct, t_cmd *command, t_env *env);
void					ms_echo(t_sct *sct);
void					ms_pwd(t_sct *sct);
void					ms_env(t_sct *sct);
void					ms_export(t_sct *sct, t_env **env);
void					ms_unset(t_sct *sct, t_env **env);
void					ms_cd(t_sct *sct, t_env **env);
void					ms_exit(t_sct *sct, t_env *e);
void					ms_free_sct(t_sct *sct);
void					ms_free_cmd(t_cmd **lst);
void					ms_free_env(t_env **lst);
void					ms_free_args(t_arg **lst);
void					ms_free_output(t_output **lst);
void					ms_free_tab(char **tab);
int						ms_free_parse(int res, char *msg, t_parse *parse);
void					ms_reset_fd(t_sct *sct, int check);

#endif
