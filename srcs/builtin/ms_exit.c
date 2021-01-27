/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 18:41:16 by alidy             #+#    #+#             */
/*   Updated: 2021/01/27 15:15:28 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ms_free_sct(t_sct *sct)
{
	ms_free_tab(sct->args);
	ms_free_tab(sct->envp);
	ms_free_cmd(sct->saved_cmds);
}

int		ms_exit_test(char *str)
{
	int i;

	i = 0;
	if (str[i] == '-' || ft_isdigit(str[i]))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int		ms_exit_args(int i, t_sct *sct)
{
	if (i > 2)
	{
		ft_printf("exit\n");
		ft_printf("Minishell: exit: too many arguments\n");
		sct->status = 1;
		return (FALSE);
	}
	return (TRUE);
}

void	ms_exit_util(t_sct *sct, int *res)
{
	if (!ms_exit_test(sct->args[1]))
	{
		ft_printf("exit\nMinishell: ");
		ft_printf("exit: %s: numeric argument required\n", sct->args[1]);
		*res = 255;
	}
	else
		*res = ft_atoi(sct->args[1]);
}

void	ms_exit(t_sct *sct, t_env *env)
{
	int i;
	int res;

	i = 1;
	res = EXIT_SUCCESS;
	while (sct->args[i])
		i++;
	if (!ms_exit_args(i, sct))
		return ;
	if (i == 2)
		ms_exit_util(sct, &res);
	if (sct->in_pipe == FALSE)
	{
		ms_free_sct(sct);
		ms_free_env(&env);
		ft_printf("exit\n");
	}
	exit(res);
}
