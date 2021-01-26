/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:51:01 by alidy             #+#    #+#             */
/*   Updated: 2021/01/26 08:35:41 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void		ms_add_command(m_cmd **commands, m_cmd *command)
{
	m_cmd *temp;

	temp = *commands;
	if (!*commands)
		*commands = command;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = command;
	}
}

void		ms_add_output(char *output, int type, m_output **lst)
{
	m_output *new;
	m_output *temp;

	new = ms_new_output(output, type);
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

void		ms_add_arg(char *content, m_arg **lst)
{
	m_arg *new;
	m_arg *temp;

	new = ms_new_arg(content);
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

int			ms_is_char_printable(int c)
{
	if (c >= 33 && c <= 126)
		return (TRUE);
	return (FALSE);
}

int			ms_check_pipe(m_cmd *cmd, char *line, int i)
{
	if (cmd->args == 0 && cmd->output == 0)
		return (TRUE);
	while (line[i])
	{
		if (line[i] == ';' || line[i] == '|')
			return (TRUE);
		if (ms_is_char_printable(line[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}
