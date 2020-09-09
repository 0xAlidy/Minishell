/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.le-101.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 03:40:07 by alidy             #+#    #+#             */
/*   Updated: 2020/02/14 18:06:04 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_write_flags(int zero, int c, int flag, int nb)
{
	if (nb < 0 && flag)
		write(1, "-", 1);
	while (c > 0)
	{
		if (flag == 1)
			write(1, "0", 1);
		else
			write(1, " ", 1);
		c--;
	}
	if (nb < 0 && !flag)
		write(1, "-", 1);
	while (zero > 0)
	{
		write(1, "0", 1);
		zero--;
	}
}

void	ft_write_justify_flags(int zero, char *numb, int size, int nb)
{
	if (nb < 0)
		write(1, "-", 1);
	while (zero > 0)
	{
		write(1, "0", 1);
		zero--;
	}
	if (nb < 0)
		write(1, numb + 1, size - 1);
	else
		write(1, numb, size);
}

void	ft_write_space(int c)
{
	while (c > 0)
	{
		write(1, " ", 1);
		c--;
	}
}

void	ft_init_int(int nb, int *s, int *z, t_flags t)
{
	(*z) = 0;
	if (nb < 0)
		(*s) = ft_intlen(nb) - 1;
	else
		(*s) = ft_intlen(nb);
	if (nb == 0 && t.precision <= 0 && t.point == 1)
		(*s) = 0;
	if (nb == 0 && t.precision < -1 && t.point == 1)
		(*s) = 1;
	if (t.precision - (*s) > 0)
		(*z) = t.precision - (*s);
	if (nb < 0)
		(*s) += 1;
}

int		ft_int_format(t_flags tab, int nb)
{
	int		size;
	int		c;
	int		zero;
	int		res;
	char	*numb;

	c = 0;
	ft_init_int(nb, &size, &zero, tab);
	if (tab.width - size - zero > 0)
		c = tab.width - size - zero;
	res = size + zero + c;
	numb = ft_itoa(nb);
	if (tab.neg == 0)
	{
		ft_write_flags(zero, c, tab.zero, nb);
		(nb < 0) ? (write(1, numb + 1, size - 1)) : (write(1, numb, size));
	}
	else
	{
		ft_write_justify_flags(zero, numb, size, nb);
		ft_write_space(c);
	}
	free(numb);
	return (res);
}
