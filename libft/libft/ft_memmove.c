/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.le-101.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 22:29:34 by alidy             #+#    #+#             */
/*   Updated: 2020/02/14 18:08:23 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dest;
	const char		*source;

	dest = dst;
	source = src;
	if (!dest && !source)
		return (0);
	if (dest < (unsigned char *)source)
		return (ft_memcpy(dst, src, len));
	while (len)
	{
		dest[len - 1] = source[len - 1];
		len--;
	}
	return (dest);
}
