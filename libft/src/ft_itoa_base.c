/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.le-101.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 06:47:41 by alidy             #+#    #+#             */
/*   Updated: 2020/02/14 18:06:01 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int				ft_nb_char(unsigned long long nb, int len)
{
	int size;
	int mod;

	mod = 0;
	size = 0;
	if (nb == 0)
		size = 1;
	while (nb > 0)
	{
		mod = nb % len;
		nb = nb / len;
		size++;
	}
	return (size);
}

char			*ft_itoa_base(int nb, char *base)
{
	int				len;
	int				mod;
	char			*res;
	int				size;
	unsigned int	temp;

	len = ft_strlen(base);
	temp = nb;
	size = ft_nb_char(temp, len);
	if (!(res = ft_calloc((size + 1), sizeof(char))))
		return (0);
	while (temp > 0)
	{
		mod = temp % len;
		temp = temp / len;
		res[size - 1] = base[mod];
		size--;
	}
	return (res);
}

char			*ft_ullitoa_base(unsigned long long nb, char *base)
{
	int				len;
	int				mod;
	char			*res;
	int				size;

	len = ft_strlen(base);
	size = ft_nb_char(nb, len);
	if (!(res = ft_calloc((size + 1), sizeof(char))))
		return (0);
	if (nb == 0)
	{
		free(res);
		res = ft_strdup("0");
	}
	while (nb > 0)
	{
		mod = nb % len;
		nb = nb / len;
		res[size - 1] = base[mod];
		size--;
	}
	return (res);
}

void			ft_strtoupper(char **str)
{
	int i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] >= 'a' && (*str)[i] <= 'z')
			(*str)[i] = (*str)[i] - 32;
		i++;
	}
}

unsigned int	ft_longlen(unsigned int nb)
{
	int		res;

	res = 0;
	if (nb == 0)
		res = 1;
	while (nb > 0)
	{
		nb = nb / 10;
		res++;
	}
	return (res);
}
