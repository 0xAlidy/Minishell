/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 16:52:58 by alidy             #+#    #+#             */
/*   Updated: 2021/01/20 16:53:05 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    ms_unset(m_sct *sct, m_env **env)
{
    m_env   *temp;
    int     i;
    int     check;
    int     save;
    char    *content;
    char    *name;

    i = 1;
    save = 0;
    temp = *env;
    while (sct->args[i])
    {
        check = FALSE;
        temp = *env;
        if ((save = ms_indexchr(sct->args[i], '=')) > 0)
        {
            content = ft_strdup(sct->args[i] + save + 1);
            name = ft_substr(sct->args[i], 0, save);
            while (temp && !check)
            {
                if (!strncmp(temp->name, name, ft_strlen(name)))
                {
                    free(temp->content);
                    temp->content = content;
                    check = TRUE;
                }
                temp = temp->next;
            }
            if (!check)
                ms_add_env(name, content, env);
        }
        i++;
    }
    sct->status = 0;
    ms_free_envp(sct->envp);
}