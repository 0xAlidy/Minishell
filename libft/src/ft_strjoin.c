/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 10:44:31 by alidy             #+#    #+#             */
/*   Updated: 2021/01/06 14:35:07 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size_s1;
	int		size_s2;
	char	*str;

	if (s1 && s2)
	{
		size_s1 = ft_strlen(s1);
		size_s2 = ft_strlen(s2);
		if ((str = malloc((size_s1 + size_s2 + 1) * sizeof(char))) == NULL)
			return (0);
		size_s1 = -1;
		size_s2 = -1;
		while (s1[++size_s1])
			str[size_s1] = s1[size_s1];
		while (s2[++size_s2])
			str[size_s1 + size_s2] = s2[size_s2];
		str[size_s1 + size_s2] = 0;
	}
	else
		str = 0;
	return (str);
}
