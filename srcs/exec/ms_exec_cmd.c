/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 13:45:31 by alidy             #+#    #+#             */
/*   Updated: 2021/01/27 15:16:17 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ms_exec_absol(t_sct *sct, t_cmd *command, t_env *env)
{
	int res;

	if (!sct->in_pipe && !sct->in_fork)
		ms_exec_fork(sct, command, env);
	else
	{
		if ((res = ms_test_path(sct->args[0], sct)) < 1)
		{
			ms_reset_fd(sct, 3);
			if (res == 0)
			{
				ft_printf("%s: No such file or directory\n", sct->args[0]);
				sct->status = 127;
			}
			ms_free_tab(sct->args);
			ms_free_tab(sct->envp);
			return (FALSE);
		}
		else
			execve(sct->args[0], sct->args, sct->envp);
	}
	return (TRUE);
}

int		ms_exec_env(t_sct *sct, t_cmd *command, t_env *env)
{
	if (!sct->in_pipe && !sct->in_fork)
		ms_exec_fork(sct, command, env);
	else
	{
		sct->path = ms_search_env("PATH", &env);
		sct->path = ms_search_path(sct);
		if (!sct->path)
		{
			ms_reset_fd(sct, 3);
			ft_printf("Minishell: %s: command not found\n", sct->args[0]);
			sct->status = 127;
			ms_free_tab(sct->args);
			ms_free_tab(sct->envp);
			return (FALSE);
		}
		execve(sct->path, sct->args, sct->envp);
		free(sct->path);
		sct->path = 0;
	}
	return (TRUE);
}

void	ms_exec_free_tab(t_sct *sct)
{
	ms_free_tab(sct->args);
	ms_free_tab(sct->envp);
}

void	ms_exec_simple_command(t_sct *sct, t_cmd *command, t_env *env)
{
	ms_transfort_args(sct, &(command->args));
	ms_set_envp(sct, &env);
	sct->status = 0;
	if ((ms_set_redirections(sct, command)) == -1)
	{
		ms_exec_free_tab(sct);
		return ;
	}
	if (strchr(sct->args[0], '/'))
	{
		if (!ms_exec_absol(sct, command, env))
			return ;
	}
	else if (ms_handler_builtin(sct, env))
	{
		ms_exec_free_tab(sct);
		return ;
	}
	else
	{
		if (!ms_exec_env(sct, command, env))
			return ;
	}
	ms_exec_free_tab(sct);
}
