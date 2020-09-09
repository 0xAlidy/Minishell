/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.le-101.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 10:15:14 by alidy             #+#    #+#             */
/*   Updated: 2020/02/14 18:07:19 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	size;
	char	*s1;

	size = 0;
	if (s)
	{
		if (start >= ft_strlen(s) || len <= 0)
		{
			if (!(s1 = malloc(1 * sizeof(char))))
				return (0);
			s1[0] = '\0';
			return (s1);
		}
		while (s[start + size] && size < len)
			size++;
		if (!(s1 = malloc((size + 1) * sizeof(char))))
			return (0);
		s1[size] = 0;
		len = -1;
		while (++len < size)
			s1[len] = s[start + len];
	}
	else
		s1 = 0;
	return (s1);
}
