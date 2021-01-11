/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 03:14:43 by alidy             #+#    #+#             */
/*   Updated: 2021/01/06 14:36:36 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_intlen(int nb)
{
	int		res;
	long	temp;

	res = 0;
	temp = nb;
	if (temp <= 0)
	{
		temp = temp * -1;
		res = 1;
	}
	while (temp > 0)
	{
		temp = temp / 10;
		res++;
	}
	return (res);
}
