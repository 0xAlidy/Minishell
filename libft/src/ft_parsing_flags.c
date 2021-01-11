/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_flags.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 03:38:47 by alidy             #+#    #+#             */
/*   Updated: 2021/01/06 14:35:59 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

t_flags	ft_init_struct(void)
{
	t_flags	tab;

	tab.zero = 0;
	tab.point = 0;
	tab.neg = 0;
	tab.width = -1;
	tab.precision = -1;
	tab.c = 0;
	return (tab);
}

int		ft_while_function(char *str, int i, t_flags *tab)
{
	while (str[i] == '0' || str[i] == '-')
	{
		if (str[i] == '-')
		{
			tab->neg = 1;
			tab->zero = 0;
		}
		else if (tab->neg == 0)
			tab->zero = 1;
		i += 1;
	}
	return (i);
}

void	ft_parsing_flags(t_flags *tab, char *str)
{
	int i;

	i = 0;
	if (str[i] == '-')
	{
		tab->neg = 1;
		i++;
	}
	i = ft_while_function(str, i, tab);
	if (str[i] >= '0' && str[i] <= '9')
		tab->width = ft_atoi(str + i);
	while ((str[i] >= '0' && str[i] <= '9') || str[i] == '-' || str[i] == '*')
		i++;
	if (str[i] == '.')
	{
		i++;
		tab->zero = 0;
		tab->point = 1;
		if (str[i] != '*')
			tab->precision = ft_atoi(str + i);
	}
	while ((str[i] >= '0' && str[i] <= '9') || str[i] == '-' || str[i] == '*')
		i++;
	tab->c = str[i];
}
