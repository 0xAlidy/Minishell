/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_gnl_eof.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 11:30:55 by alidy             #+#    #+#             */
/*   Updated: 2021/01/23 08:40:21 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		ms_gnl_eof(int fd, char **line)
{
    char            *temp;
	char			buffer[BUFFER_SIZE + 1];
	int				res;

	buffer[BUFFER_SIZE] = 0;
	if (!line || (res = BUFFER_SIZE) < 1 || read(fd, buffer, 0) < 0)
		return (-1);
	while ((res != 0 && !ft_gnl_strchr(temp, '\n')) || (res == 0 && temp[0] != 0))
	{
		if ((res = read(fd, buffer, BUFFER_SIZE)) < 0
		|| (!(temp = ft_gnl_strjoin(temp, buffer, res))))
			return (-1);
	}
	if (res == 0)
    {
        free(temp);
		return (-2);
    }
    else
    {
        if (!(*line = ft_gnl_strdup(temp)))
		    return (-1);
        free(temp);
    }
	return (1);
}