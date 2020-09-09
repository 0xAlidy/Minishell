/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.le-101.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 12:32:48 by alidy             #+#    #+#             */
/*   Updated: 2020/02/14 18:08:45 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list		*liste;
	t_list		*maillon;

	liste = NULL;
	maillon = NULL;
	while (lst != 0)
	{
		if ((maillon = ft_lstnew((*f)(lst->content))) == NULL)
		{
			ft_lstclear(&liste, (*del));
			return (liste);
		}
		ft_lstadd_back(&liste, maillon);
		lst = lst->next;
	}
	return (liste);
}
