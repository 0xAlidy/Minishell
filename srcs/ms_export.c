/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 11:17:19 by alidy             #+#    #+#             */
/*   Updated: 2021/01/22 10:02:02 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

m_env    *ms_cpy_env(m_env **env)
{
    m_env *temp;
    m_env *res;

    temp = *env;
    res = 0;
    while (temp)
    {
        ms_add_env(ft_strdup(temp->name), ft_strdup(temp->content), &res);
        temp = temp->next;
    }
    return (res);
}

m_env   **ms_sort_env(m_env **env)
{
    m_env   **s;
    m_env   *lst;
    m_env   *temp;
    char    *save;
    int     swap;

    lst = ms_cpy_env(env);
    s = &lst;
    temp = *s;
    swap = TRUE;
    while (swap)
    {
        swap = FALSE;
        temp = lst;
        while (temp->next)
        {
            if (strncmp(temp->name,temp->next->name, ft_strlen(temp->name)) > 0)
            {
                save = temp->name;
                temp->name = temp->next->name;
                temp->next->name = save;
                save = temp->content;
                temp->content = temp->next->content;
                temp->next->content = save;
                swap = TRUE;
            }
            temp = temp->next;
        }
    }
    return (s);
}
void    ms_print_export(m_env **env)
{
    int     len;
    m_env   **lst;
    m_env   *temp;
    m_env   *save;

    len = 0;
    lst = ms_sort_env(env);
    temp = *lst;
    while (temp)
    {
        ft_printf("declare -x %s=\"%s\"\n", temp->name, temp->content);
        ft_strfree(temp->name, temp->content, 3);
        save = temp;
        temp = temp->next;
        free(save);
    }
}

int     ms_modify_env(m_env **env, char *name, char *content)
{
    m_env *temp;

    temp = *env;
    while (temp)
    {
        if (!strncmp(temp->name, name, ft_strlen(name) + 1))
        {
            free(temp->content);
            temp->content = content;
            return (TRUE);
        }
        temp = temp->next;
    }
    return (FALSE);
}

void    ms_export(m_sct *sct, m_env **env)
{
    int     i;
    int     save;
    char    *content;
    char    *name;

    i = 1;
    save = 0;
    while (sct->args[i])
    {
        if ((save = ms_indexchr(sct->args[i], '=')) > 0)
        {
            content = ft_strdup(sct->args[i] + save + 1);
            name = ft_substr(sct->args[i], 0, save);
            if (!ms_modify_env(env, name, content))
                ms_add_env(name, content, env);
            else
                free(name);
        }
        i++;
    }
    if (i == 1)
        ms_print_export(env);
    sct->status = 0;
}