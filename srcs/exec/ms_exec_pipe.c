/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 15:19:14 by alidy             #+#    #+#             */
/*   Updated: 2021/01/27 15:35:28 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ms_pipe_end_2(t_sct *sct, int *save_fd, int *pipefd[2])
{
	if (wait(&sct->status) < 0)
		exit(EXIT_FAILURE);
	sct->status = 0;
	close((*pipefd)[1]);
	*save_fd = (*pipefd)[0];
}

void	ms_pipe_end(int *last, t_cmd **command)
{
	if (*last != TRUE)
		(*command) = (*command)->next;
	if (*last == FALSE && !(*command)->pipe)
		*last = TRUE;
	else
		*last = FALSE;
}

void	ms_pipe_inter(t_sct *sct, int save_fd, t_cmd **cmd, int *pipefd[2])
{
	sct->saved_stdout = dup(STDOUT_FILENO);
	dup2(save_fd, 0);
	if ((*cmd)->next)
		dup2((*pipefd)[1], STDOUT_FILENO);
	close((*pipefd)[0]);
}

void	ms_exec_pipe(t_sct *sct, t_cmd **command, t_env *env)
{
	int		pipefd[2];
	pid_t	pid;
	int		save_fd;
	int		last;

	save_fd = 0;
	last = FALSE;
	while (*command && ((*command)->pipe || last == TRUE))
	{
		if (pipe(pipefd) == -1)
			exit(EXIT_FAILURE);
		if ((pid = fork()) == -1)
			exit(sct->status);
		else if (pid == 0)
		{
			ms_pipe_inter(sct, save_fd, command, &pipefd);
			ms_exec_simple_command(sct, *command, env);
			exit(sct->status);
		}
		else
		{
			ms_pipe_end_2(sct, &save_fd, &pipefd);
			ms_pipe_end(&last, command);
		}
	}
}
