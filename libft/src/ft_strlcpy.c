/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 11:29:51 by alidy             #+#    #+#             */
/*   Updated: 2021/01/06 14:34:50 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t		ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t i;
	size_t size_src;

	i = 0;
	if (!dest)
		return (0);
	if (src)
	{
		size_src = ft_strlen(src);
		if (size == 0)
			return (size_src);
		while (i < size - 1 && src[i])
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = 0;
	}
	else
	{
		dest = 0;
		size_src = 0;
	}
	return (size_src);
}
