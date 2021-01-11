/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:14:42 by alidy             #+#    #+#             */
/*   Updated: 2021/01/06 14:34:16 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

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
	maillon = ft_lstnew(fd, liste);
	return (maillon);
}

t_gnl	*ft_lstnew(int fd, t_gnl **liste)
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
