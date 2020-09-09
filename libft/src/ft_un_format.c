/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_un_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.le-101.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 09:11:34 by alidy             #+#    #+#             */
/*   Updated: 2020/02/14 18:05:47 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char			*ft_litoa(unsigned int n)
{
	int				nb_c;
	int				i;
	unsigned int	save;
	char			*str;

	nb_c = 0;
	save = n;
	if (n == 0)
		nb_c++;
	while (save > 0)
	{
		nb_c++;
		save = save / 10;
	}
	i = nb_c - 1;
	if ((str = malloc(sizeof(char) * (nb_c + 1))) == NULL)
		return (0);
	str[nb_c] = 0;
	while (i >= 0)
	{
		str[i] = (n % 10 + 48);
		n = n / 10;
		i--;
	}
	return (str);
}

char			*ft_test_un(t_flags tab, unsigned int nb)
{
	char *numb;

	numb = ft_litoa(nb);
	if (nb == 0 && tab.precision == 0 && tab.width != -1)
	{
		free(numb);
		numb = 0;
	}
	if (nb == 0 && tab.width == -1 && tab.precision == 0)
	{
		free(numb);
		return (0);
	}
	return (numb);
}

void			ft_init_un(t_flags tab, int size, int *zero, int *c)
{
	if (tab.precision - size > 0)
		(*zero) = tab.precision - size;
	if (tab.width - size - (*zero) > 0)
		(*c) = tab.width - size - (*zero);
}

void			ft_init_size(int *size, int nb, t_flags t)
{
	if (nb == 0 && t.precision == 0 && t.point == 1)
		(*size) = 0;
	else
		(*size) = ft_longlen(nb);
}

int				ft_un_format(t_flags tab, unsigned int nb)
{
	int		size;
	int		c;
	int		zero;
	int		res;
	char	*numb;

	zero = 0;
	c = 0;
	ft_init_size(&size, nb, tab);
	ft_init_un(tab, size, &zero, &c);
	res = size + zero + c;
	numb = ft_test_un(tab, nb);
	if (tab.neg == 0)
	{
		ft_write_flags(zero, c, tab.zero, 1);
		write(1, numb, size);
	}
	else
	{
		ft_write_justify_flags(zero, numb, size, 1);
		ft_write_space(c);
	}
	free(numb);
	return (res);
}
