/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 14:26:48 by alidy             #+#    #+#             */
/*   Updated: 2021/01/27 15:16:06 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ms_reset_fd(t_sct *sct, int check)
{
	if (sct->saved_stdout != -1 && (check == 1 || check == 3))
	{
		dup2(sct->saved_stdout, STDOUT_FILENO);
		close(sct->saved_stdout);
		sct->saved_stdout = -1;
	}
	if (sct->saved_stdin != -1 && (check == 2 || check == 3))
	{
		dup2(sct->saved_stdin, STDIN_FILENO);
		close(sct->saved_stdin);
		sct->saved_stdin = -1;
	}
}

int		ms_simple_input(t_sct *sct, t_output *temp)
{
	int fd;

	ms_reset_fd(sct, 2);
	sct->saved_stdin = dup(STDIN_FILENO);
	if ((fd = open(temp->content, O_RDONLY)) == -1)
	{
		ms_reset_fd(sct, 3);
		ft_printf("Minishell : %s: %s\n", temp->content, strerror(errno));
		sct->status = 1;
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (TRUE);
}

int		ms_double_output(t_sct *sct, t_output *temp)
{
	int fd;

	ms_reset_fd(sct, 1);
	sct->saved_stdout = dup(STDOUT_FILENO);
	if (!(fd = open(temp->content, O_WRONLY | O_CREAT | O_APPEND,
	S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)))
	{
		ms_reset_fd(sct, 3);
		ft_printf("Minishell : %s: %s\n", temp->content, strerror(errno));
		sct->status = 1;
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (TRUE);
}

int		ms_simple_output(t_sct *sct, t_output *temp)
{
	int fd;

	ms_reset_fd(sct, 1);
	sct->saved_stdout = dup(STDOUT_FILENO);
	if (!(fd = open(temp->content, O_WRONLY | O_CREAT | O_TRUNC,
	S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)))
	{
		ms_reset_fd(sct, 3);
		ft_printf("Minishell : %s: %s\n", temp->content, strerror(errno));
		sct->status = 1;
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (TRUE);
}

int		ms_set_redirections(t_sct *sct, t_cmd *command)
{
	t_output *temp;

	temp = command->output;
	while (temp)
	{
		if (temp->type == 1)
		{
			if (ms_simple_input(sct, temp) == -1)
				return (-1);
		}
		else if (temp->type == 2)
		{
			if (ms_simple_output(sct, temp) == -1)
				return (-1);
		}
		else
		{
			if (ms_double_output(sct, temp) == -1)
				return (-1);
		}
		temp = temp->next;
	}
	return (TRUE);
}
