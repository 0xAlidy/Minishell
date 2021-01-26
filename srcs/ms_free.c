/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 08:13:01 by alidy             #+#    #+#             */
/*   Updated: 2021/01/26 10:23:59 by alidy            ###   ########lyon.fr   */
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

void    ms_free_tab(char **tab)
{
    int i;

    i = 0;
    if (tab)
    {
        while (tab[i])
        {
            free(tab[i]);
            i++;
        }
        free(tab);
    }
    tab = 0;
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