/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 08:24:14 by alidy             #+#    #+#             */
/*   Updated: 2021/01/18 09:58:07 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    ft_echo(m_sct *sct)
{
    int i;
    int option;

    i = 0;
    option = FALSE;
    while (sct->args[i])
    {
        if (i == 0 && !ft_strncmp(sct->args[i], "-n", 2))
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