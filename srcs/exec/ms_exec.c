/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 10:10:45 by alidy             #+#    #+#             */
/*   Updated: 2021/01/27 15:36:40 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ms_fork_status(t_sct *sct)
{
	if (sct->status == 2)
		sct->status = 130;
	else if (sct->status == 3)
		sct->status = 131;
}

void	ms_exec_fork(t_sct *sct, t_cmd *command, t_env *env)
{
	pid_t pid;

	ms_signal_handler(2);
	if ((pid = fork()) == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		sct->in_fork = TRUE;
		ms_exec_simple_command(sct, command, env);
		exit(sct->status);
	}
	else
	{
		if (wait(&sct->status) < 0)
			exit(EXIT_FAILURE);
		if (WIFEXITED(sct->status))
			sct->status = WEXITSTATUS(sct->status);
		else if (WIFSIGNALED(sct->status))
			ms_fork_status(sct);
		command = command->next;
	}
	ms_signal_handler(1);
}

void	ms_exec_commands(t_sct *sct, t_cmd **commands, t_env *env)
{
	t_cmd *command;

	command = *commands;
	sct->saved_cmds = commands;
	while (command)
	{
		sct->in_fork = FALSE;
		if (command->pipe)
		{
			sct->in_pipe = TRUE;
			ms_exec_pipe(sct, &command, env);
		}
		else
		{
			sct->in_pipe = FALSE;
			ms_exec_simple_command(sct, command, env);
		}
		ms_reset_fd(sct, 3);
		if (command)
			command = command->next;
	}
}
