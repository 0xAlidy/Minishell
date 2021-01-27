/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 11:17:19 by alidy             #+#    #+#             */
/*   Updated: 2021/01/27 15:15:28 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ms_print_export(t_env **env)
{
	int		len;
	t_env	**lst;
	t_env	*temp;
	t_env	*save;

	len = 0;
	lst = ms_sort_env(env);
	temp = *lst;
	while (temp)
	{
		ft_printf("declare -x %s=\"%s\"\n", temp->name, temp->content);
		ft_strfree(temp->name, temp->content, 3);
		save = temp;
		temp = temp->next;
		free(save);
	}
}

int		ms_modify_env(t_env **env, char *name, char *content)
{
	t_env *temp;

	temp = *env;
	while (temp)
	{
		if (!strncmp(temp->name, name, ft_strlen(name) + 1))
		{
			free(temp->content);
			temp->content = content;
			return (TRUE);
		}
		temp = temp->next;
	}
	return (FALSE);
}

int		ms_export_util(t_sct *sct, int i, int *j)
{
	while (sct->args[i][*j] && sct->args[i][*j] != '=')
	{
		if ((*j == 0 && !ft_isalpha(sct->args[i][*j]))
		|| (*j != 0 && !ft_isalnum(sct->args[i][*j])))
		{
			ft_printf("Minishell: export: ");
			ft_printf("`%s':not a valid identifier\n", sct->args[i]);
			sct->status = 1;
			return (FALSE);
		}
		(*j)++;
	}
	if (*j == 0)
	{
		ft_printf("Minishell: export: ");
		ft_printf("`%s':not a valid identifier\n", sct->args[i]);
		sct->status = 1;
		return (FALSE);
	}
	return (TRUE);
}

void	ms_export(t_sct *sct, t_env **env)
{
	int		i;
	int		j;
	char	*content;
	char	*name;

	i = 0;
	while (sct->args[++i])
	{
		j = 0;
		if (!ms_export_util(sct, i, &j))
			return ;
		if (sct->args[i][j])
		{
			name = ft_substr(sct->args[i], 0, j);
			content = ft_strdup(sct->args[i] + j + 1);
			if (!ms_modify_env(env, name, content))
				ms_add_env(name, content, env);
			else
				free(name);
		}
	}
	if (i == 1)
		ms_print_export(env);
}
