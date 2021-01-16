/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 21:59:37 by alidy             #+#    #+#             */
/*   Updated: 2021/01/16 08:40:54 by alidy            ###   ########lyon.fr   */
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
    int             args;
    int             output;
    int             save;
    int             in_squote;
    int             in_dquote;
    int             in_input;
    int             in_output;
    int             in_dollar;
    int             is_double;
    char            *content;
}                   m_parse;

/* Liste des fichiers d'output */

typedef struct          s_output
{
    char                *content;
    int                 is_double;
    struct s_output     *next;
}                       m_output;

/* Liste des commandes entrees par l'utilisateur */

typedef struct		s_cmd
{
    m_arg           *args;
    char            *input;
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

char                *ms_get_env(char **env, char *key);
char                *ms_current_folder();
m_cmd               *set_commands(char *line, m_env *env);
int                 set_command(char *line, int i, m_cmd *command, m_env *env);
m_env               *set_env(char **tab);
char                *search_env(char *str, m_env **lst);


#endif