/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_gnl_eof.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 11:30:55 by alidy             #+#    #+#             */
/*   Updated: 2021/01/27 13:32:10 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ms_gnl_eof(int fd, char **line)
{
	char	*t;
	char	buffer[BUFFER_SIZE + 1];
	int		r;

	buffer[BUFFER_SIZE] = 0;
	if (!line || (r = BUFFER_SIZE) < 1 || read(fd, buffer, 0) < 0)
		return (-1);
	while ((r != 0 && !ft_gnl_strchr(t, '\n')) || (r == 0 && t[0] != 0))
	{
		if ((r = read(fd, buffer, BUFFER_SIZE)) < 0
		|| (!(t = ft_gnl_strjoin(t, buffer, r))))
			return (-1);
	}
	if (r == 0)
	{
		free(t);
		return (-2);
	}
	else
	{
		if (!(*line = ft_gnl_strdup(t)))
			return (-1);
		free(t);
	}
	return (1);
}
