/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 16:52:58 by alidy             #+#    #+#             */
/*   Updated: 2021/01/21 13:28:07 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    ms_unset(m_sct *sct, m_env **env)
{
    m_env   *temp;
    m_env   *before;
    int     find;
    int     i;

    i = 1;
    while (sct->args[i])
    {
        temp = *env;
        before = 0;
        find = FALSE;
        while (temp && find == FALSE)
        {
            if (!strncmp(temp->name, sct->args[i], ft_strlen(sct->args[i]) + 1))
            {
                if (!before)
                    env = &(temp->next);
                else
                    before->next = temp->next;
                free(temp->content);
                free(temp->name);
                free(temp);
                find = TRUE;
            }
            if (find == FALSE)
            {
                before = temp; 
                temp = temp->next;
            }
        }
        i++;
    }
    sct->status = 0;
}