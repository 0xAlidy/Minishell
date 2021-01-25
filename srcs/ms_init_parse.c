/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:47:40 by alidy             #+#    #+#             */
/*   Updated: 2021/01/25 16:51:25 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

m_parse		ms_init_parse(void)
{
	m_parse parse;

	parse.save = 0;
	parse.content = 0;
	parse.type_output = 0;
	parse.in_slash = FALSE;
	parse.in_squote = FALSE;
	parse.in_dquote = FALSE;
	parse.in_dollar = FALSE;
	return (parse);
}

m_output	*ms_new_output(char *output, int type)
{
	m_output *new;

	if (!(new = malloc(sizeof(m_output))))
		exit(EXIT_FAILURE);
	new->content = ft_strdup(output);
	new->type = type;
	new->next = 0;
	return (new);
}

m_arg		*ms_new_arg(char *arg)
{
	m_arg *new;

	if (!(new = malloc(sizeof(m_arg))))
		exit(EXIT_FAILURE);
	new->content = ft_strdup(arg);
	new->next = 0;
	return (new);
}

m_cmd		*ms_new_command(void)
{
	m_cmd *command;

	if (!(command = malloc(sizeof(m_cmd))))
		exit(EXIT_FAILURE);
	command->args = 0;
	command->output = 0;
	command->pipe = FALSE;
	command->next = 0;
	return (command);
}
