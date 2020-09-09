/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.le-101.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:14:42 by alidy             #+#    #+#             */
/*   Updated: 2020/02/14 18:07:08 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_gnl	*recup_maillon(int fd, t_gnl **liste)
{
	t_gnl	*maillon;
	t_gnl	*tmp;

	maillon = *liste;
	if (maillon)
		while (maillon)
		{
			tmp = maillon->next;
			if (fd == maillon->fd)
				return (maillon);
			maillon = tmp;
		}
	maillon = ft_lstnew_gnl(fd, liste);
	return (maillon);
}

t_gnl	*ft_lstnew_gnl(int fd, t_gnl **liste)
{
	t_gnl	*maillon;

	if (!(maillon = malloc(sizeof(t_gnl))))
		return (0);
	maillon->fd = fd;
	maillon->content = 0;
	maillon->next = *liste;
	*liste = maillon;
	return (maillon);
}

int		rm_lst(int fd, t_gnl **lst)
{
	t_gnl	*maillon;
	t_gnl	*temp;

	maillon = *lst;
	temp = 0;
	if (maillon->fd == fd)
	{
		*lst = maillon->next;
		free(maillon->content);
		free(maillon);
		return (0);
	}
	while ((maillon->next)->fd != fd)
		maillon = (*lst)->next;
	temp = maillon->next;
	maillon->next = (maillon->next)->next;
	free(temp->content);
	free(temp);
	return (0);
}

int		ft_strchr_gnl(char *s, int c)
{
	int i;

	i = 0;
	if (s)
		while (s[i])
		{
			if (s[i] == c)
				return (1);
			i++;
		}
	return (0);
}

int		ft_strlen_gnl(char *s)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
			i++;
	}
	return (i);
}
