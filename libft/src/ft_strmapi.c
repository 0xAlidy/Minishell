/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:21:59 by alidy             #+#    #+#             */
/*   Updated: 2021/01/06 14:34:45 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;
	unsigned int	size;

	if (s)
	{
		i = 0;
		size = ft_strlen(s);
		if ((str = malloc(sizeof(char) * (size + 1))) == NULL)
			return (0);
		while (i < size)
		{
			str[i] = (*f)(i, s[i]);
			i++;
		}
		str[i] = 0;
	}
	else
		str = 0;
	return (str);
}
