/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 08:13:01 by alidy             #+#    #+#             */
/*   Updated: 2021/01/27 15:16:17 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ms_free_env(t_env **lst)
{
	t_env *temp;
	t_env *save;

	temp = *lst;
	save = *lst;
	while (temp)
	{
		save = temp->next;
		free(temp->name);
		free(temp->content);
		temp = save;
	}
	*lst = 0;
}

void	ms_free_tab(char **tab)
{
	int i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
	tab = 0;
}

void	ms_free_cmd(t_cmd **lst)
{
	t_cmd *temp;
	t_cmd *save;

	temp = *lst;
	save = *lst;
	while (temp)
	{
		save = temp->next;
		ms_free_args(&temp->args);
		ms_free_output(&temp->output);
		free(temp);
		temp = save;
	}
	*lst = 0;
}

void	ms_free_output(t_output **lst)
{
	t_output *temp;
	t_output *save;

	temp = *lst;
	save = *lst;
	while (temp)
	{
		save = temp->next;
		free(temp->content);
		free(temp);
		temp = save;
	}
}

void	ms_free_args(t_arg **lst)
{
	t_arg *temp;
	t_arg *save;

	temp = *lst;
	save = *lst;
	while (temp)
	{
		save = temp->next;
		free(temp->content);
		free(temp);
		temp = save;
	}
}
