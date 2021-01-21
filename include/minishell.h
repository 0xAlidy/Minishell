/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 21:59:37 by alidy             #+#    #+#             */
/*   Updated: 2021/01/21 13:17:59 by alidy            ###   ########lyon.fr   */
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

/* Liste des variables d'environnement */

typedef struct      s_env
{
    char            *name;
    char            *content;
    struct s_env    *next;
}                   m_env;

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
}                   m_sct;

char                *ms_get_env(char **env, char *key);
m_env               *ms_new_env(char *name, char *content);
void                ms_add_env(char *name, char *content, m_env **lst);
m_env               *ms_set_env(char **tab);
char                *ms_search_env(char *str, m_env **lst);
char                *ms_current_folder();
m_sct               ms_init_sct();
char                *ms_minitrim(char *str);
int                 ms_indexchr(char *s, int c);
void                ms_prompt(void);
void                ms_signal_handler(int signum);
m_cmd               *ms_set_commands(char *line, m_env *env);
int                 ms_set_command(char *line, int i, m_cmd *command, m_env *env);
void                ms_exit_shell(char *str, int exit_status, m_sct *sct);
void                ms_exec_simple_command(m_sct *sct, m_cmd *command, m_env *env);
void                ms_exec_commands(m_sct *sct, m_cmd **commands, m_env *env);
void                ms_echo(m_sct *sct);
void                ms_pwd(m_sct *sct);
void                ms_env(m_sct *sct);
void                ms_export(m_sct *sct, m_env **env);
void                ms_unset(m_sct *sct, m_env **env);
void                ms_free_cmd(m_cmd **lst);
void                ms_free_sct(m_sct *sct);
void                ms_free_env(m_env **lst);
void                ms_free_args(m_arg **lst);
void                ms_free_output(m_output **lst);
void                ms_free_envp(char **envp);


#endif