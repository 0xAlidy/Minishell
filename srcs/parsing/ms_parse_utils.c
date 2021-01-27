/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:51:01 by alidy             #+#    #+#             */
/*   Updated: 2021/01/27 15:16:17 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void		ms_add_command(t_cmd **commands, t_cmd *command)
{
	t_cmd *temp;

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

void		ms_add_output(char *output, int type, t_output **lst)
{
	t_output *new;
	t_output *temp;

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

void		ms_add_arg(char *content, t_arg **lst)
{
	t_arg *new;
	t_arg *temp;

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

int			ms_check_end(t_parse *parse, char *line, int i)
{
	char save;

	save = line[i];
	i--;
	while (i >= 0)
	{
		if (line[i] == ';')
			return (ms_free_parse(-1, ";", parse));
		if (line[i] == '|')
			return (ms_free_parse(-1, "|", parse));
		if (ms_is_char_printable(line[i]))
			return (TRUE);
		i--;
	}
	if (save == '|')
		return (ms_free_parse(-1, "|", parse));
	return (ms_free_parse(-1, ";", parse));
}
