/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.le-101.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 11:31:01 by alidy             #+#    #+#             */
/*   Updated: 2020/02/14 21:18:42 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strfree(char *s1, char *s2, int fr)
{
	if (fr == 1 && s1)
		free(s1);
	else if (fr == 2 && s2)
		free(s2);
	else if (fr == 3 && (s1 || s2))
	{
		if (s1)
			free(s1);
		if (s2)
			free(s2);
	}
}

char	*ft_strjoin_free(char *s1, char *s2, int free)
{
	int		size_s1;
	int		size_s2;
	char	*str;

	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	if (!(str = malloc((size_s1 + size_s2 + 1) * sizeof(char))))
		return (0);
	str[size_s1 + size_s2] = 0;
	size_s1 = 0;
	size_s2 = 0;
	if (s1)
		while (s1[size_s1])
		{
			str[size_s1] = s1[size_s1];
			size_s1++;
		}
	if (s2)
		while (s2[size_s2])
		{
			str[size_s1 + size_s2] = s2[size_s2];
			size_s2++;
		}
	ft_strfree(s1, s2, free);
	return (str);
}
