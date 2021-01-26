/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 16:52:58 by alidy             #+#    #+#             */
/*   Updated: 2021/01/26 09:10:43 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    ms_unset(m_sct *sct, m_env **env)
{
    m_env   *temp;
    m_env   *before;
    int     find;
    int     i;
    int     j;

    i = 1;
    j = 0;
    while (sct->args[i])
    {
        temp = *env;
        before = 0;
        find = FALSE;
        j = 0;
        while (sct->args[i][j])
        {
            if ((j == 0 && !ft_isalpha(sct->args[i][j])) || (j != 0 && !ft_isalnum(sct->args[i][j])))
            {
                ft_printf("Minishell: export: `%s': not a valid identifier\n", sct->args[i]);
                sct->status = 1;
                return;
            }  
            j++;
        }
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