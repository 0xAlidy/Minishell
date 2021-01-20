/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 08:24:14 by alidy             #+#    #+#             */
/*   Updated: 2021/01/20 08:54:15 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    ms_echo(m_sct *sct)
{
    int i;
    int option;

    i = 1;
    option = FALSE;
    while (sct->args[i])
    {
        if (i == 1 && !ft_strncmp(sct->args[i], "-n", 3))
            option = TRUE;
        else
        {
            ft_printf("%s", sct->args[i]);
            if (sct->args[i + 1])
                ft_printf(" ");
        }
        i++;
    }
    if (option == FALSE)
        ft_printf("\n");
}