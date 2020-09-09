/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.le-101.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 09:52:35 by alidy             #+#    #+#             */
/*   Updated: 2020/02/14 18:07:29 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *dest, const char *src, size_t len)
{
	size_t i;
	size_t y;

	i = 0;
	y = 0;
	if (*src == 0)
		return ((char *)dest);
	while (dest[i] && len > i)
	{
		if (dest[i] == src[y])
		{
			while (dest[i + y] && dest[i + y] == src[y] && len > i + y)
				y++;
			if (src[y] == 0)
				return ((char *)&dest[i]);
		}
		i++;
		y = 0;
	}
	return (0);
}
