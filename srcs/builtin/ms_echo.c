/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 08:24:14 by alidy             #+#    #+#             */
/*   Updated: 2021/01/26 21:23:50 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ms_is_option(char *str)
{
	int i;

	i = 0;
	if (str[i++] != '-')
		return (FALSE);
	while (str[i])
	{
		if (str[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	ms_echo(m_sct *sct)
{
	int i;
	int option;
	int stop;

	i = 1;
	option = FALSE;
	stop = FALSE;
	while (sct->args[i])
	{
		if (stop == FALSE && ms_is_option(sct->args[i]))
			option = TRUE;
		else
		{
			ft_printf("%s", sct->args[i]);
			if (sct->args[i + 1])
				ft_printf(" ");
			stop = TRUE;
		}
		i++;
	}
	if (option == FALSE)
		ft_printf("\n");
}
