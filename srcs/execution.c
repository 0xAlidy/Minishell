/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 10:10:45 by alidy             #+#    #+#             */
/*   Updated: 2021/01/16 13:08:51 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *search_path(char *file, m_env *env)
{
    int i;
    int save;
    char *path ;
    char *current_path = 0;
    struct stat buf;
    
    i = 0;
    save = 0;
    path = search_env("PATH", &env);
    while (path[i])
    {
        save = i;
        while (path[i] != ':') 
            i++;
        current_path = ft_substr(path, save, i);
        if (path[i - 1] != '/')
            current_path = ft_strjoin_free(current_path, '/', 1);
        current_path = ft_strjoin_free(current_path, file, 1);
        if(stat(path, &buf) == 0)
        {
            if (S_ISREG(buf.st_mode))
            {
                free(path);
                return (current_path);
            }
            free(current_path);
        }
        i++; 
    }
    errno = ENOENT; // command not found
    return (0);
}

char    **transform_args(char **cmd, m_arg **args)
{
    int     len;
    char    **res;
    m_arg   *temp;

    temp = *args;
    len = 0;
    while (temp->next)
    {
        len++;
        temp = temp->next;
    }
    if (!(res = malloc(len * sizeof(char *))))
        exit(EXIT_FAILURE);
    res[len - 1] = 0;
    temp = *args;
    len = 0;
    while (temp->next)
    {
        if (len == 0)
            *cmd = ft_strdup(temp->content); // set cmd
        else
            res[len - 1] = ft_strdup(temp->content);
        len++;
        temp = temp->next;
    }
    return (res);
}

void exec_commands(m_cmd **commands, m_env *env)
{
    char    *path;
    char    *cmd;
    char    **args;
    m_cmd   *temp;
    

    path = 0;
    cmd = 0;
    args = 0;
    temp = *commands;
    while (temp)
    {
        if (builtin) // si un bultin
        {
            // run
        }
        else // fork and exec
        {
            args = transform_args(&cmd, &(temp->args));
            if(strchr(cmd, '/')) // si un chemin (error : No such file or directory)
                execv(cmd, args);
            else // sinon chercher dans l'env
            {
                path = search_path(cmd, env);
                if (!path) // commande existe pas  (error: command not found)
                    return 0;
                execv(path, args);
                free(path);
            }
        }
        temp = temp->next;
    }
    
    return (0);

}