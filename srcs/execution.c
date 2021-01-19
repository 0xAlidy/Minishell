/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 10:10:45 by alidy             #+#    #+#             */
/*   Updated: 2021/01/19 11:30:53 by alidy            ###   ########lyon.fr   */
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
            current_path = ft_strjoin_free(current_path, "/", 1);
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

void    reset_fd(m_sct *sct, int check)
{
    if (sct->saved_stdout != -1 && (check == 1 || check == 3))
    {
        dup2(sct->saved_stdout, 1);
        close(sct->saved_stdout);
        sct->saved_stdout = -1;
    }   
    if (sct->saved_stdin != -1 && (check == 2 || check == 3))
    {
        dup2(sct->saved_stdin, 0);
        close(sct->saved_stdin);
        sct->saved_stdin = -1;
    }
}

void    set_redirections(m_sct *sct, m_cmd *command)
{
    m_output    *temp;
    int         fd;

    temp = command->output;
    while (temp)
    {
        if (temp->type == 1)
        {
            reset_fd(sct, 2);
            sct->saved_stdin = dup(STDIN_FILENO);
            if ((fd = open(temp->content, O_RDONLY)) == -1)
            {
                reset_fd(sct, 3);
                ft_printf("%s: %s\n", temp->content, strerror(errno));
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDIN_FILENO); // stdin
            close(fd);
        }
        if (temp->type == 2)
        {
            reset_fd(sct, 1);
            sct->saved_stdout = dup(STDOUT_FILENO);
            if (!(fd = open(temp->content, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)))
                exit(EXIT_FAILURE); //erreur
            dup2(fd, STDOUT_FILENO); 
            close(fd);
        }
        else
        {
            reset_fd(sct, 1);
            sct->saved_stdout = dup(STDOUT_FILENO);
            if (!(fd = open(temp->content, O_WRONLY | O_CREAT | O_APPEND
			| S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)))
                exit(EXIT_FAILURE); //erreur
            dup2(fd, 1); // stdout
            close(fd);
        }
        temp = temp->next;
    }
 
}

void    set_envp(m_sct *sct, m_env **env)
{
    int     len;
    m_env   *temp;

    temp = *env;
    len = 0;
    while (temp->next)
    {
        len++;
        temp = temp->next;
    }
    if (!(sct->envp = malloc((len + 1) * sizeof(char *))))
        exit(EXIT_FAILURE);
    sct->envp[len] = 0;
    temp = *env;
    len = 0;
    while (temp->next)
    {
        sct->envp[len] = ft_strdup(temp->name);
        sct->envp[len] = ft_strjoin_free(sct->envp[len], "=", 1);
        sct->envp[len] = ft_strdup(temp->content);
        temp = temp->next;
    }
}

void    transform_args(m_sct *sct, m_arg **args)
{
    int     len;
    m_arg   *temp;

    temp = *args;
    len = 0;
    while (temp->next)
    {
        len++;
        temp = temp->next;
    }
    if (!(sct->args = malloc((len + 1) * sizeof(char *))))
        exit(EXIT_FAILURE);
    sct->args[len] = 0;
    temp = *args;
    len = 0;
    while (temp)
    {
        // si j'ai $? sans \t je remplace
        // ft_minitrim_remove(temp->content)je trime les \t en rien
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
        ft_exit_shell(0, EXIT_FAILURE, sct);
    else if (pid == 0)
    {
        exec_simple_command(sct, command, env);
        ft_exit_shell(0, EXIT_SUCCESS, sct);
    }
    else
    {
        if (wait(&sct->status) < 0)
            exit(EXIT_FAILURE); // exit + free tout
        command = command->next;
    }
}

int    handler_builtin(m_sct *sct, m_env *env)
{
    (void)env;
    if (!ft_strncmp(sct->cmd, "echo", 5))
        ft_echo(sct);
    else if (!ft_strncmp(sct->cmd, "pwd", 4))
        ft_pwd(sct);
    /*else if (!ft_strncmp(sct->cmd, "cd", 3))
        ft_cd(sct, env);
    else if (!ft_strncmp(sct->cmd, "export", 7))
        ft_export(sct, env);
    else if (!ft_strncmp(sct->cmd, "unset", 6))
        ft_unset(sct, env);
    else if (!ft_strncmp(sct->cmd, "env", 4))
        ft_env(sct, env);*/
    else if (!ft_strncmp(sct->cmd, "exit", 5))
        exit(EXIT_SUCCESS);
        //ft_exit(sct);
    else
        return (FALSE);
    return (TRUE);
}

void    exec_simple_command(m_sct *sct, m_cmd *command, m_env *env)
{
    char *path;

    path = 0;
    transform_args(sct, &(command->args));
    if (!sct->envp)
        set_envp(sct, &env);
    set_redirections(sct, command);
    if (strchr(sct->cmd, '/')) // si un chemin (error : No such file or directory)
    {
        if (!sct->in_pipe)
            exec_fork(sct, command, env);
        else
            execve(path, sct->args, sct->envp); // in pipe
    }
    else if (handler_builtin(sct, env)) // si un built in
       return;
    else // sinon chercher dans l'env
    {
        search_path(sct, env);
        if (!path) // commande existe pas  (error: command not found)
            exit(EXIT_FAILURE);
        if (!sct->in_pipe)
            exec_fork(sct, command, env);
        else
            execve(path, sct->args, sct->envp); // in pipe
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
    while (command->pipe)
    {
        if (pipe(pipefd) == -1)
            ft_exit_shell(0, EXIT_FAILURE, sct);
        if ((pid = fork()) == -1)
            ft_exit_shell(0, EXIT_FAILURE, sct);
        else if (pid == 0)
        {
            dup2(save_fd, 0); //change the input according to the old one 
            if (command->next)
                dup2(pipefd[1], 1);
            close(pipefd[0]);
            exec_simple_command(sct, command, env);
            ft_exit_shell(0, EXIT_SUCCESS, sct);
        }
        else
        {
            if (wait(&sct->status) < 0)
                exit(EXIT_FAILURE); // exit + free tout
            close(pipefd[1]);
            save_fd = pipefd[0]; //save the input for the next command
            command = command->next;
            if (last == FALSE && !command->pipe)
                last = TRUE;
        }
    }
}

void    exec_commands(m_sct *sct, m_cmd **commands, m_env *env)
{
    m_cmd   *command;

    command = *commands;
    while (command)
    {
        if (command->pipe)
        {
            sct->in_pipe = TRUE;
            exec_pipe(sct, command, env);
        }
        else
        {
            sct->in_pipe = FALSE;
            exec_simple_command(sct, command, env);
        }
        reset_fd(sct, 3);
        command = command->next;
    }
}