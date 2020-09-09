/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_str_format.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.le-101.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 03:34:35 by alidy             #+#    #+#             */
/*   Updated: 2020/02/14 18:06:11 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*ft_init_join(char *s1, char *s2)
{
	int		size_s1;
	int		size_s2;
	char	*str;

	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	if (!(str = malloc((size_s1 + size_s2 + 1) * sizeof(char))))
		return (0);
	str[size_s1 + size_s2] = 0;
	return (str);
}

char	*ft_fstrjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!(str = ft_init_join(s1, s2)))
		return (0);
	i = 0;
	j = 0;
	if (s1)
		while (s1[i])
		{
			str[i] = s1[i];
			i++;
		}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	if (s1)
		free(s1);
	free(s2);
	return (str);
}

void	ft_test_star(const char *s, int i, va_list list, t_flags *tab)
{
	int save;

	save = 0;
	if (s[i] == '*')
	{
		if (s[i - 1] == '.')
			tab->precision = va_arg(list, int);
		else
		{
			save = va_arg(list, int);
			if (save < 0)
			{
				tab->neg = 1;
				tab->width = -save;
			}
			else
				tab->width = save;
		}
	}
}

char	*ft_get_str_format(const char *s, int *i, va_list list, t_flags *tab)
{
	char	*res;
	char	*temp;
	char	*nb;
	int		save;

	save = *i;
	nb = 0;
	res = 0;
	while (s[*i] != '%' && s[*i] != 'X' && (s[*i] < 'a' || s[*i] > 'z'))
	{
		ft_test_star(s, *i, list, tab);
		(*i) += 1;
	}
	temp = ft_substr(s, save, *i - save + 1);
	res = ft_fstrjoin(res, temp);
	return (res);
}
