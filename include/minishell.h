/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 21:59:37 by alidy             #+#    #+#             */
/*   Updated: 2021/01/26 11:24:25 by alidy            ###   ########lyon.fr   */
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

/* Liste des arguments de ma commande */

typedef struct      s_arg  
{
    char            *content;
    struct s_arg    *next;
}                   m_arg;

/* Liste des variables d'environnement */

typedef struct      s_env
{
    char            *name;
    char            *content;
    struct s_env    *next;
}                   m_env;

/* Variables pour faire le parsing des commands */

typedef struct      s_parse
{
    int             save;
    int             type_output;
    int             in_squote;
    int             in_dquote;
    int             in_dollar;
    int             in_slash;
    int             is_double;
    char            *content;
	m_env 			**env;
}                   m_parse;

/* Liste des fichiers d'output */

typedef struct          s_output
{
    char                *content;
    int                 type;
    struct s_output     *next;
}                       m_output;

/* Liste des commandes entrees par l'utilisateur */

typedef struct		s_cmd
{
    m_arg           *args;
    m_output        *output;
    int             pipe;
	struct s_cmd	*next;
}                   m_cmd;



/* Variables pendant l'execution des commandes */

typedef struct      s_sct
{
    int             status;
    int             in_pipe;
    int             in_fork;
    char            **args;
    char            *path;
    char            **envp;
    int             saved_stdout;
    int             saved_stdin;
    m_cmd           **saved_cmds;
}                   m_sct;

m_cmd               *ms_set_commands(char *line, m_env **env, m_sct *sct);
int     			ms_set_command(char *line, int i, m_cmd *command, m_env **env);
int    				ms_set_content(char *line, int i, m_parse *parse, m_cmd *cmd);
int					ms_parse_line(char *line, int i, m_parse *parse, m_cmd *command);
char				*ms_create_dollar(char *str, int i, m_parse *parse);
void				ms_create_string(char *line, int i, m_parse *parse);
int					ms_parse_arg(char *line, int i, m_parse *parse);
m_parse				ms_init_parse(m_env **env);
m_output			*ms_new_output(char *output, int type);
m_arg				*ms_new_arg(char *arg);
m_cmd				*ms_new_command();
int					ms_free_parse(int res, char *msg, m_parse *parse);
void				ms_add_command(m_cmd **commands, m_cmd *command);
void				ms_add_output(char *output, int type, m_output **lst);
void				ms_add_arg(char *content, m_arg **lst);
int					ms_is_char_printable(int c);
int     			ms_check_pipe(m_cmd *cmd, char *line, int i);
void				ms_create_space(char *line, int *i, m_parse *parse);
int                 ms_handler_slash(char *line, int *i, m_parse *parse);
void                ms_handler_dollar(char *line, int *i, m_parse *parse);
void                ms_handler_quotes(char *line, int *i, m_parse *parse);




void                ms_debug_struct(m_cmd **cmds); // a enlever
void    			ms_print_tab(char **tab); // a enlever
int		            ms_gnl_eof(int fd, char **line);
char                *ms_get_env(char **env, char *key);
m_env               *ms_new_env(char *name, char *content);
void                ms_add_env(char *name, char *content, m_env **lst);
m_env               *ms_set_env(char **tab);
char                *ms_search_env(char *str, m_env **lst);
int                 ms_modify_env(m_env **env, char *name, char *content);
char                *ms_current_folder();
m_sct               ms_init_sct();
char                *ms_minitrim(char *str);
int                 ms_indexchr(char *s, int c);
void                ms_prompt(void);
void                ms_signal_handler(int type);
void                ms_exec_simple_command(m_sct *sct, m_cmd *command, m_env *env);
void                ms_exec_commands(m_sct *sct, m_cmd **commands, m_env *env);
void                ms_echo(m_sct *sct);
void                ms_pwd(m_sct *sct);
void                ms_env(m_sct *sct);
void                ms_export(m_sct *sct, m_env **env);
void                ms_unset(m_sct *sct, m_env **env);
void                ms_cd(m_sct *sct, m_env **env);
void                ms_exit(m_sct *sct, m_env *env);
void    			ms_free_sct(m_sct *sct);
void                ms_free_cmd(m_cmd **lst);
void                ms_free_env(m_env **lst);
void                ms_free_args(m_arg **lst);
void                ms_free_output(m_output **lst);
void                ms_free_tab(char **tab);
int                 ms_free_parse(int res, char *msg, m_parse *parse);
void    			ms_reset_fd(m_sct *sct, int check);

#endif