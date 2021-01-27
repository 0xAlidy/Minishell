/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 09:50:05 by alidy             #+#    #+#             */
/*   Updated: 2021/01/27 15:15:54 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ms_set_content(char *line, int i, t_parse *parse, t_cmd *cmd)
{
	if ((i = ms_parse_arg(line, i, parse)) == -1)
		return (-1);
	if (parse->in_squote == TRUE || parse->in_dquote == TRUE)
		return (ms_free_parse(-1, "quotes", parse));
	ms_create_string(line, i, parse);
	if (!(parse->none == TRUE && parse->content[0] == 0))
	{
		if (parse->type_output)
			ms_add_output(parse->content, parse->type_output, &(cmd->output));
		else
			ms_add_arg(parse->content, &(cmd->args));
	}
	free(parse->content);
	parse->content = 0;
	parse->type_output = 0;
	parse->none = FALSE;
	return (i);
}

int		ms_parse_line(char *line, int i, t_parse *parse, t_cmd *command)
{
	while (line[i] && line[i] != '|' && line[i] != ';')
	{
		if (line[i] != '>' && line[i] != '<' && line[i] != ' ')
			if ((i = ms_set_content(line, i, parse, command)) == -1)
				return (-1);
		if (line[i] == '>' || line[i] == '<')
		{
			if (parse->type_output)
				return (ms_free_parse(-1, "newline", parse));
			if (line[i] == '>')
			{
				parse->type_output = 2;
				if (line[i + 1] == '>')
				{
					parse->type_output = 3;
					i++;
				}
			}
			else
				parse->type_output = 1;
		}
		if (line[i] && line[i] != '|' && line[i] != ';')
			i++;
	}
	return (i);
}

int		ms_set_command(char *line, int i, t_cmd *command, t_env **env)
{
	t_parse parse;

	parse = ms_init_parse(env);
	if ((i = ms_parse_line(line, i, &parse, command)) == -1)
		return (-1);
	if (parse.type_output)
		return (ms_free_parse(-1, "newline", &parse));
	if (ms_check_end(&parse, line, i) == -1)
		return (-1);
	if (line[i] == '|')
		command->pipe = TRUE;
	return (ms_free_parse(i, 0, &parse));
}

t_cmd	*ms_set_commands(char *line, t_env **env, t_sct *sct)
{
	int		i;
	t_cmd	*commands;
	t_cmd	*command;

	i = 0;
	commands = 0;
	while (line[i])
	{
		command = ms_new_command();
		if ((i = ms_set_command(line, i, command, env)) == -1)
		{
			ms_free_cmd(&command);
			ms_free_cmd(&commands);
			sct->status = 258;
			return (0);
		}
		ms_add_command(&commands, command);
		if (line[i])
			i++;
	}
	free(line);
	return (commands);
}
