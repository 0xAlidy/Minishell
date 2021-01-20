/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 11:17:19 by alidy             #+#    #+#             */
/*   Updated: 2021/01/20 12:01:40 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    ms_export(m_sct *sct, m_env **env)
{
    m_env   *temp;
    int     i;
    int     check;
    int     save;
    char    *content;
    char    *name;

    i = 0;
    save = 0;
    temp = *env;
    check = FALSE;
    while (sct->args[i])
    {
        if (save = ms_indexchr(sct->args[i], "=") + 1)
        {
            content = ft_strdup(sct->args[i] + save);
            name = ft_substr(sct->args[i], 0, save);
            while (temp && !check)
            {
                if (!strncmp(temp->name, name, ft_strlen(name) + 1))
                {
                    free(temp->content);
                    temp->content = content;
                    check = TRUE;
                }
                temp = temp->next;
            }
            if (!check)
                ms_add_env(name, content, env);
            ft_strfree(content, name, 3);
        }
        i++;
    }
    sct->status = 0;
    ms_free_envp(sct->envp);
}