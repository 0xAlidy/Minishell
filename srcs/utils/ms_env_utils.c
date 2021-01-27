/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 10:24:55 by alidy             #+#    #+#             */
/*   Updated: 2021/01/27 15:15:17 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*ms_new_env(char *name, char *content)
{
	t_env *env;

	if (!(env = malloc(sizeof(t_env))))
		exit(EXIT_FAILURE);
	env->name = name;
	env->content = content;
	env->next = 0;
	return (env);
}

void	ms_add_env(char *name, char *content, t_env **lst)
{
	t_env *new;
	t_env *temp;

	new = ms_new_env(name, content);
	temp = *lst;
	if (!*lst)
		*lst = new;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

char	*ms_search_env(char *str, t_env **lst)
{
	t_env *temp;

	temp = *lst;
	if (!*lst)
		return (0);
	else
	{
		while (temp)
		{
			if (!ft_strncmp(str, temp->name, ft_strlen(str) + 1))
				return (ft_strdup(temp->content));
			temp = temp->next;
		}
	}
	return (0);
}

void	ms_set_env_util(int j, char **tab, char **name, char **content)
{
	int i;
	int save;

	i = 0;
	save = 0;
	while (tab[j][i])
	{
		if (tab[j][i] == '=')
		{
			*name = ft_substr(tab[j], 0, i);
			save = i + 1;
		}
		i++;
	}
	*content = ft_substr(tab[j], save, i - save);
}

t_env	*ms_set_env(char **tab)
{
	t_env	*lst;
	int		j;
	char	*name;
	char	*content;

	lst = 0;
	j = 0;
	name = 0;
	content = 0;
	while (tab[j])
	{
		ms_set_env_util(j, tab, &name, &content);
		ms_add_env(name, content, &lst);
		j++;
	}
	return (lst);
}
