/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.le-101.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:14:28 by alidy             #+#    #+#             */
/*   Updated: 2020/02/15 19:16:22 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_gnl(char *s1, char *s2, int limit)
{
	int		size_s1;
	int		size_s2;
	char	*str;

	size_s1 = ft_strlen_gnl(s1);
	size_s2 = limit;
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
	while (s2[size_s2] && size_s2 < limit)
	{
		str[size_s1 + size_s2] = s2[size_s2];
		size_s2++;
	}
	free(s1);
	return (str);
}

char	*ft_strdup_gnl(char *s1)
{
	int		i;
	char	*s2;

	i = 0;
	while (s1[i] && s1[i] != '\n')
		i++;
	if (!(s2 = (char *)malloc(sizeof(char) * (i + 1))))
		return (0);
	s2[i] = 0;
	i = 0;
	while (s1[i] && s1[i] != '\n')
	{
		s2[i] = s1[i];
		i++;
	}
	return (s2);
}

char	*ft_remove(char *current)
{
	int		i;
	int		y;
	char	*res;
	int		size;

	i = 0;
	size = ft_strlen_gnl(current);
	y = 0;
	while (current[i] != '\n')
		i++;
	i++;
	if (!(res = malloc((size - i + 1) * sizeof(char))))
		return (0);
	res[size - i] = 0;
	while (i + y < size)
	{
		res[y] = current[i + y];
		y++;
	}
	free(current);
	return (res);
}

int		get_next_line(int fd, char **line)
{
	static t_gnl	*list;
	t_gnl			*temp;
	char			buffer[BUFFER_SIZE + 1];
	int				res;
	int				ok;

	buffer[BUFFER_SIZE] = 0;
	if (!line || (res = BUFFER_SIZE) < 1 || read(fd, buffer, 0) < 0
	|| (!(temp = recup_maillon(fd, &list))))
		return (-1);
	while (!(ok = ft_strchr_gnl(temp->content, '\n')) && res == BUFFER_SIZE)
	{
		if ((res = read(fd, buffer, BUFFER_SIZE)) < 0
		|| (!(temp->content = ft_strjoin_gnl(temp->content, buffer, res))))
			return (-1);
	}
	if (!(*line = ft_strdup_gnl(temp->content)))
		return (-1);
	if (res < BUFFER_SIZE && !ok && rm_lst(fd, &list) == 0)
		return (0);
	if ((temp->content = ft_remove(temp->content)) == 0)
		return (-1);
	return (1);
}
