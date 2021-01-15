/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 10:24:55 by alidy             #+#    #+#             */
/*   Updated: 2021/01/15 12:10:22 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

m_env       *new_env(char *name, char *content)
{
    m_env *env;

    if (!(env = malloc(sizeof(m_env))))
        exit(EXIT_FAILURE);
    env->name = name;
    env->content = content;
    env->next = 0;
    return (env);
}

void       add_env(char *name, char *content, m_env **lst)
{
    m_env *new;
    m_env *temp;

    new = new_env(name, content);
    temp = *lst;
    if (!*lst)
        *lst = new;
    else
    {
        while (temp->next)
            temp = temp->next;
        temp->next = new;
    }
}

char        *search_env(char *str, m_env **lst)
{
    m_env *temp;

    temp = *lst;
    if (!*lst)
        return (0);
    else
    {
        while (temp)
        {
            if (!temp)
                return (0);
            if (ft_strncmp(str, temp->name,ft_strlen(str)))
                return (ft_strdup(temp->content)); 
            temp = temp->next;
        }
    }
    return (0);
}

m_env       *set_env(char **tab)
{
    m_env   *lst;
    int     i;
    int     j;
    int     save;
    char    *name;
    char    *content;

    lst = 0;
    i = 0;
    j = 0;
    name = 0;
    content = 0;
    save = 0;
    while (tab[j])
    {
        while(tab[j][i])
        {
            if (tab[j][i] == '=')
            {
                name = ft_substr(tab[j], 0, i);
                save = i + 1;
            }
            i++;
        }
        i = 0;
        content = ft_substr(tab[j], save, i - save);
        add_env(name, content, &lst);
        j++;
    }
    return (lst);
}