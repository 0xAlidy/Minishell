/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 09:43:56 by alidy             #+#    #+#             */
/*   Updated: 2021/01/17 12:11:22 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    ft_exit(char *str, int exit_status, m_sct *sct)
{
    if (exit_status > 0)
    {
        if (str)
            ft_printf("Minishell: %s : %s", str, strerror(errno));
        else
            ft_printf("Minishell: %s", strerror(errno));
    }
    errno = 0; // a voir
    sct->status = exit_status;
    exit(sct->status);
}

void    free_minishell(m_cmd **cmds, m_env *env)
{
    ;
}