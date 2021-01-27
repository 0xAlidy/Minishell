/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:47:40 by alidy             #+#    #+#             */
/*   Updated: 2021/01/27 15:16:17 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_parse		ms_init_parse(t_env **env)
{
	t_parse parse;

	parse.save = 0;
	parse.env = env;
	parse.content = 0;
	parse.type_output = 0;
	parse.none = FALSE;
	parse.in_slash = FALSE;
	parse.in_squote = FALSE;
	parse.in_dquote = FALSE;
	parse.in_dollar = FALSE;
	return (parse);
}

t_output	*ms_new_output(char *output, int type)
{
	t_output *new;

	if (!(new = malloc(sizeof(t_output))))
		exit(EXIT_FAILURE);
	new->content = ft_strdup(output);
	new->type = type;
	new->next = 0;
	return (new);
}

t_arg		*ms_new_arg(char *arg)
{
	t_arg *new;

	if (!(new = malloc(sizeof(t_arg))))
		exit(EXIT_FAILURE);
	new->content = ft_strdup(arg);
	new->next = 0;
	return (new);
}

t_cmd		*ms_new_command(void)
{
	t_cmd *command;

	if (!(command = malloc(sizeof(t_cmd))))
		exit(EXIT_FAILURE);
	command->args = 0;
	command->output = 0;
	command->pipe = FALSE;
	command->next = 0;
	return (command);
}

int			ms_free_parse(int res, char *msg, t_parse *parse)
{
	if (parse->content)
		free(parse->content);
	if (msg)
	{
		ft_printf("Minishell: syntax error near unexpected token : ");
		ft_printf("'%s'\n", msg);
	}
	return (res);
}
