/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 12:53:08 by alidy             #+#    #+#             */
/*   Updated: 2021/01/22 13:00:01 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    ms_sigint_one()
{
    ft_printf("\n");
    ms_prompt();
}

void    ms_sigint_two()
{
    ft_printf("\n");
    signal(SIGQUIT, SIG_DFL);
}

void    ms_sigquit()
{
    ft_printf("Quit:\n");
    signal(SIGQUIT, SIG_DFL);
}

void    ms_signal_handler(int type)
{
    if (type == 1)
    {
        signal(SIGINT, ms_sigint_one);
        signal(SIGQUIT, SIG_IGN);
    }
    else if (type == 2)
    {
        signal(SIGINT, ms_sigint_two);
        signal(SIGQUIT, ms_sigquit);
    }
}