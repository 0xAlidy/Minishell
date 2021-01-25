/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 08:13:01 by alidy             #+#    #+#             */
/*   Updated: 2021/01/25 16:17:59 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    ms_free_env(m_env **lst)
{
    m_env *temp;
    m_env *save;

    temp = *lst;
    save = *lst;
    while (temp)
    {
        save = temp->next;
        free(temp->name);
        free(temp->content);
        temp = save;
    }
}

void    ms_free_envp(char **envp)
{
    int i;

    i = 0;
    while (envp && envp[i])
    {
        free(envp[i]);
        i++;
    }
    if (envp)
        free(envp);
    envp = 0;
}

void    ms_free_sct(m_sct *sct)
{
    int i;

    i = 0;
    if (sct->path)
        free(sct->path);
    sct->path = 0;
    
    while (sct->args && sct->args[i])
    {
        free(sct->args[i]);
        i++;
    }
    if (sct->args)
        free(sct->args);
    sct->args = 0;
    ms_free_envp(sct->envp);
    ms_free_cmd(sct->saved_cmds);
}

void    ms_free_cmd(m_cmd **lst)
{
    m_cmd *temp;
    m_cmd *save;

    temp = *lst;
    save = *lst;
    while (temp)
    {
        save = temp->next;
        ms_free_args(&temp->args);
        ms_free_output(&temp->output);
        free(temp);
        temp = save;
    }
    *lst = 0;
}

void    ms_free_output(m_output **lst)
{
    m_output *temp;
    m_output *save;

    temp = *lst;
    save = *lst;
    while (temp)
    {
        save = temp->next;
        free(temp->content);
        free(temp);
        temp = save;
    }
}

void    ms_free_args(m_arg **lst)
{
    m_arg *temp;
    m_arg *save;

    temp = *lst;
    save = *lst;
    while (temp)
    {
        save = temp->next;
        free(temp->content);
        free(temp);
        temp = save;
    }
}