/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 10:15:51 by alidy             #+#    #+#             */
/*   Updated: 2021/01/06 14:34:52 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t		ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	size_src;
	size_t	size_dest;

	i = 0;
	size_src = ft_strlen(src);
	size_dest = ft_strlen(dest);
	if (size_dest >= size)
		return (size_src + size);
	while ((size_dest + i < size - 1) && src[i])
	{
		dest[i + size_dest] = src[i];
		i++;
	}
	dest[i + size_dest] = 0;
	return (size_dest + size_src);
}
