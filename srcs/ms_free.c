/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 18:59:31 by alidy             #+#    #+#             */
/*   Updated: 2021/01/19 19:10:30 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    ms_free_env(m_env **env)
{
    m_env *temp;
    m_env *save;

    temp = *lst;
    save = *lst;
    while (temp)
    {
        save = temp->next;
        free(temp->name)
        free(temp->content);
        temp = save;
    }
}

void    ms_free_sct(m_sct *sct)
{
    int i;

    i = 0;
    if (sct->cmd)
        free(sct->cmd);
    if (sct->path)
        free(sct->path);
    while (sct->args && sct->args[i])
    {
        free(sct->args[i])
        i++;
    }
    if (sct->args)
        free(sct->args)
    i = 0;
    while (sct->envp && sct->envp[i])
    {
        free(sct->envp[i])
        i++;
    }
    if (sct->envp)
        free(sct->envp);
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

void    ms_free_args(m_arg **args)
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