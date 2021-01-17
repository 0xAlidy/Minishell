/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 10:10:45 by alidy             #+#    #+#             */
/*   Updated: 2021/01/17 12:52:18 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    search_path(m_sct *sct, m_env *env)
{
    int i;
    int save;
    char *current_path;
    struct stat buf;
    
    i = 0;
    save = 0;
    current_path = 0;
    sct->path = search_env("PATH", &env);
    while (sct->path[i])
    {
        save = i;
        while (sct->path[i] != ':') 
            i++;
        current_path = ft_substr(sct->path, save, i);
        if (sct->path[i - 1] != '/')
            current_path = ft_strjoin_free(current_path, '/', 1);
        current_path = ft_strjoin_free(current_path, sct->cmd, 1);
        if (stat(sct->path, &buf) == 0)
        {
            /*if (S_ISDIR(buf.t.mod))
            {
                ft_printf("%s is a directory\n", sct->path);
                exit(1);
            }*/
            if (S_ISREG(buf.st_mode))
            {
                free(sct->path);
                sct->path = 0;
                sct->path = current_path;
                return;
            }
            free(current_path);
        }
        i++; 
    }
    errno = ENOENT; // command not found
    free(sct->path);
    sct->path = 0;
}

void    transform_args(m_sct *sct, m_arg **args)
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
    if (!(sct->args = malloc(len * sizeof(char *))))
        exit(EXIT_FAILURE);
    res[len - 1] = 0;
    temp = *args;
    len = 0;
    while (temp->next)
    {
        if (len == 0)
            sct->cmd = ft_strdup(temp->content); // set cmd
        else
            sct->args[len - 1] = ft_strdup(temp->content);
        len++;
        temp = temp->next;
    }
}

void    exec_fork(m_sct *sct, m_cmd *command, m_env *env)
{
    pid_t pid;
    
    if ((pid = fork()) == -1)
        ft_exit(0, EXIT_FAILURE, sct);
    else if (pid == 0)
    {
        exec_simple_command(sct, command, env);
        ft_exit(0, EXIT_SUCCESS, sct);
    }
    else
    {
        if (wait(&sct->status) < 0)
            exit(EXIT_FAILURE); // exit + free tout
        command = command->next;
    }
}

void    exec_simple_command(m_sct *sct, m_cmd *command, m_env *env)
{
    char *path;

    path = 0;
    transform_args(sct, &(command->args));
    set_redirection();
    if (strchr(sct->cmd, '/')) // si un chemin (error : No such file or directory)
    {
        if (!sct->in_pipe)
            exec_fork(sct, &command, env);
        else
            execv(path, sct->args); // in pipe
    }
    else if (handler_builtin) // si un built in
    {
        ;
    }
    else // sinon chercher dans l'env
    {
        search_path(sct, env);
        if (!path) // commande existe pas  (error: command not found)
                return 0;
        if (!sct->in_pipe)
            exec_fork(sct, &command, env);
        else
            execv(path, sct->args); // in pipe
        free(path);
    }   
}

void    exec_pipe(m_sct *sct, m_cmd *command, m_env *env)
{
    int     pipefd[2];
	pid_t   pid;
	int     save_fd;
    int     last;
    
    save_fd = 0;
    last = FALSE;
    while (command->pipe || last == TRUE)
    {
        if (pipe(pipefd) == -1);
            ft_exit(0, EXIT_FAILURE, sct);
        if ((pid = fork()) == -1)
            ft_exit(0, EXIT_FAILURE, sct);
        else if (pid == 0)
        {
            dup2(save_fd, 0); //change the input according to the old one 
            if (command->next)
                dup2(pipefd[1], 1);
            close(pipefd[0]);
            exec_simple_command(sct, command, env);
            ft_exit(0, EXIT_SUCCESS, sct);
        }
        else
        {
            if (wait(&sct->status) < 0)
                exit(EXIT_FAILURE); // exit + free tout
            close(pipefd[1]);
            save_fd = pipefd[0]; //save the input for the next command
            command = command->next;
            if (!command->pipe && last == FALSE)
                last = TRUE;
        }
    }
}

void    exec_commands(m_sct *sct, m_cmd **commands, m_env *env)
{
    m_cmd   *command;

    command = *commands;
    sct->start_list = commands;
    while (command)
    {
        if (command->pipe)
        {
            sct->in_pipe = TRUE;
            exec_pipe(sct, &command, env);
        }
        else
        {
            sct->in_pipe = FALSE;
            exec_simple_command(sct, command, env);
        }
        command = command->next;
    }
}