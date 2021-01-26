/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 10:29:38 by alidy             #+#    #+#             */
/*   Updated: 2021/01/26 22:09:00 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

m_env	*ms_cpy_env(m_env **env)
{
	m_env *temp;
	m_env *res;

	temp = *env;
	res = 0;
	while (temp)
	{
		ms_add_env(ft_strdup(temp->name), ft_strdup(temp->content), &res);
		temp = temp->next;
	}
	return (res);
}

void	ms_sort_env_util(m_env *temp, int *swap)
{
	char	*save;

	save = 0;
	while (temp->next)
	{
		if (strncmp(temp->name,temp->next->name, ft_strlen(temp->name)) > 0)
		{
			save = temp->name;
			temp->name = temp->next->name;
			temp->next->name = save;
			save = temp->content;
			temp->content = temp->next->content;
			temp->next->content = save;
			*swap = TRUE;
		}
		temp = temp->next;
	}
}

m_env	**ms_sort_env(m_env **env)
{
	m_env	**s;
	m_env	*lst;
	m_env	*temp;
	int		swap;

	lst = ms_cpy_env(env);
	s = &lst;
	temp = *s;
	swap = TRUE;
	while (swap)
	{
		swap = FALSE;
		temp = lst;
		ms_sort_env_util(temp, &swap);
	}
	return (s);
}

void	ms_env(m_sct *sct)
{
	int i;

	i = 0;
	while (sct->envp[i])
	{
		ft_printf("%s\n", sct->envp[i]);
		i++;
	}
	sct->status = 0;
}
