/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 21:59:37 by alidy             #+#    #+#             */
/*   Updated: 2021/01/11 14:07:47 by alidy            ###   ########lyon.fr   */
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

typedef struct		s_cmd
{
    char            **args; // arguments de ma commande
    char            *input; // fichier d'entree
    char            **output; // tableau des fichiers de sorties
    int             db_redi; // '>' ? '>>'
    int             pipe; // le separateur est il un pipe ?
	struct s_cmd	*next; // prochaine commande
}					t_cmd;

typedef struct      s_env
{
    char            *name;
    char            *content;
    struct t_cmd   *next;
}                   t_env;

char    *ms_get_env(char **env, char *key);
char    *ms_current_folder();
t_cmd  *tokenizer_input(char *line);
int     parsing_command(char *line, int i, t_cmd *command);


#endif