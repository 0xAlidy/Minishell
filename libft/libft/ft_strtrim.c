/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.le-101.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 11:03:38 by alidy             #+#    #+#             */
/*   Updated: 2020/02/14 18:07:22 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	nb_start(char const *s, char const *set)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (set[j])
	{
		if (s[i] == set[j] && s[i])
		{
			i++;
			j = 0;
		}
		else
			j++;
	}
	return (i);
}

static int	nb_end(char const *s, char const *set, int size)
{
	int j;
	int i;

	j = 0;
	i = size - 1;
	while (set[j])
	{
		if (i > 0 && s[i] == set[j])
		{
			i--;
			j = 0;
		}
		else
			j++;
	}
	return (size - i - 1);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	int		s_total;
	int		start;
	int		end;
	char	*str;
	int		i;

	i = -1;
	str = 0;
	if (s1)
	{
		if (!set)
			return (str = ft_strdup(s1));
		s_total = ft_strlen(s1);
		start = nb_start(s1, set);
		end = nb_end(s1, set, s_total);
		if (s_total - start - end <= 0)
			return (ft_strdup(""));
		if (!(str = malloc((s_total - start - end + 1) * sizeof(char))))
			return (0);
		while (start + ++i < s_total - end)
			str[i] = s1[start + i];
		str[i] = 0;
	}
	return (str);
}
