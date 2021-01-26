/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 16:52:58 by alidy             #+#    #+#             */
/*   Updated: 2021/01/26 22:06:45 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ms_unset_error(m_sct *sct, int i)
{
	int j;

	j = 0;
	while (sct->args[i][j])
	{
		if ((j == 0 && !ft_isalpha(sct->args[i][j]))
		|| (j != 0 && !ft_isalnum(sct->args[i][j])))
		{
			ft_printf("Minishell: export: `%s':\
			not a valid identifier\n", sct->args[i]);
			sct->status = 1;
			return (FALSE);
		}  
		j++;
	}
	if (j == 0)
	{
		ft_printf("Minishell: export: `%s':\
		not a valid identifier\n", sct->args[i]);
		sct->status = 1;
		return (FALSE);
	}
	return (TRUE);
}

void	ms_unset_util(m_env *temp, m_sct *sct, m_env **env, int i)
{
	int		find;
	m_env	*before;

	before = 0;
    find = FALSE;
	while (temp && find == FALSE)
	{
		if (!strncmp(temp->name, sct->args[i], ft_strlen(sct->args[i]) + 1))
		{
			if (!before)
				env = &(temp->next);
			else
				before->next = temp->next;
			free(temp->content);
			free(temp->name);
			free(temp);
			find = TRUE;
		}
		if (find == FALSE)
		{
			before = temp; 
			temp = temp->next;
		}
	}
}

void    ms_unset(m_sct *sct, m_env **env)
{
    m_env   *temp;
    int     i;

    i = 1;
    while (sct->args[i])
    {
        temp = *env;
		if (!ms_unset_error(sct, i))
			return ;
		ms_unset_util(temp, sct, env, i);
        i++;
    }
    sct->status = 0;
}