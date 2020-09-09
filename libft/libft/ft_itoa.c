/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.le-101.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 15:10:07 by alidy             #+#    #+#             */
/*   Updated: 2020/02/14 18:09:11 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		nb_char(long n)
{
	int res;

	res = 0;
	if (n == 0)
		res++;
	while (n > 0)
	{
		res++;
		n = n / 10;
	}
	return (res);
}

char			*ft_itoa(int n)
{
	int		nb_c;
	int		i;
	char	*str;
	long	temp;

	temp = n;
	temp = temp > 0 ? temp : (temp * -1);
	nb_c = n >= 0 ? 0 : 1;
	nb_c += nb_char(temp);
	i = nb_c - 1;
	if ((str = malloc(sizeof(char) * (nb_c + 1))) == NULL)
		return (0);
	str[nb_c] = 0;
	while (i >= 0)
	{
		if (n < 0 && i == 0)
			str[i] = '-';
		else
			str[i] = (temp % 10 + 48);
		temp = temp / 10;
		i--;
	}
	return (str);
}
