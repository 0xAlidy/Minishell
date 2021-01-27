/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 12:53:08 by alidy             #+#    #+#             */
/*   Updated: 2021/01/27 13:43:44 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ms_sigint_one(int num)
{
	(void)num;
	ft_printf("\n");
	ms_prompt(0);
}

void	ms_sigint_two(int num)
{
	(void)num;
	ft_printf("\n");
	signal(SIGQUIT, SIG_DFL);
}

void	ms_sigquit(int num)
{
	(void)num;
	ft_printf("Quit: 3\n");
	signal(SIGQUIT, SIG_DFL);
}

void	ms_signal_handler(int type)
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
