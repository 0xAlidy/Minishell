/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.le-101.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 02:49:43 by alidy             #+#    #+#             */
/*   Updated: 2020/02/14 18:05:50 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_char_format(t_flags tab, char c)
{
	int		i;
	int		size;
	char	z;

	i = -1;
	if (tab.zero == 1)
		z = '0';
	else
		z = ' ';
	size = tab.width;
	if (size <= 0)
		size = 1;
	if (tab.neg == 0)
	{
		while (++i < size - 1)
			write(1, &z, 1);
		write(1, &c, 1);
	}
	else
	{
		write(1, &c, 1);
		while (++i < size - 1)
			write(1, &z, 1);
	}
	return (size);
}

void	ft_write_str(int neg, int c, char *str, int size)
{
	if (neg == 0)
		while (--c > 0)
			write(1, " ", 1);
	write(1, str, size);
	if (neg == 1)
		while (--c > 0)
			write(1, " ", 1);
}

int		ft_str_format(t_flags tab, char *str)
{
	int		size;
	int		c;
	int		res;
	int		ok;

	ok = 0;
	c = 0;
	if (str == 0)
		ok = 1;
	if (str == 0)
		str = ft_strdup("(null)");
	size = ft_strlen(str);
	if (tab.precision < size && tab.precision >= 0)
		size = tab.precision;
	if (tab.width - size > 0)
		c = tab.width - size;
	res = size + c;
	c++;
	ft_write_str(tab.neg, c, str, size);
	if (ok == 1)
		free(str);
	return (res);
}
