/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 08:02:04 by alidy             #+#    #+#             */
/*   Updated: 2021/01/26 11:37:51 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ms_create_space(char *line, int *i, m_parse *parse)
{
	ms_create_string(line, *i, parse);
	parse->content = ft_strjoin_free(parse->content, "\t", 1);
	parse->save = ++(*i);
}

int		ms_handler_slash(char *l, int *i, m_parse *parse)
{
	if (l[*i + 1])
		parse->in_slash = TRUE;
	if (parse->in_dquote == FALSE && parse->in_squote == FALSE)
	{
		if (l[*i + 1] == '?')
			ms_create_space(l, i, parse);
		else
		{
			ms_create_string(l, *i, parse);
			parse->save = ++(*i);
			if (l[*i] == 0)
				return (ms_free_parse(-1, "backslash", parse));
		}
	}
	else if (parse->in_dquote == TRUE)
	{
		if (l[*i + 1] == '"' || l[*i + 1] == '$' || l[*i + 1] == '\\')
		{
			ms_create_string(l, *i, parse);
			(*i)++;
		}
	}
	return (TRUE);
}

void	ms_handler_dollar(char *line, int *i, m_parse *p)
{
	if (line[*i + 1] == '?' && (p->in_slash == TRUE || p->in_squote == TRUE))
	{
		if (p->in_squote == TRUE)
			ms_create_string(line, *i, p);
		p->content = ft_strjoin_free(p->content, "$\t", 1);
		p->save = *i + 1;
		return ;
	}
	if (!ms_is_char_printable(line[*i + 1]) || p->in_squote == TRUE
	|| line[*i + 1] == '\\' || p->in_slash == TRUE)
		return ;
	ms_create_string(line, *i, p);
	p->in_dollar = TRUE;
}

void	ms_handler_quotes(char *line, int *i, m_parse *parse)
{
	if (line[*i] == '"' && parse->in_squote == FALSE)
	{
		if (parse->in_dquote == TRUE)
			parse->in_dquote = FALSE;
		else
			parse->in_dquote = TRUE;
		ms_create_string(line, *i, parse);
	}
	else if (line[*i] == '\'' && parse->in_dquote == FALSE)
	{
		if (parse->in_squote == TRUE)
			parse->in_squote = FALSE;
		else
			parse->in_squote = TRUE;
		ms_create_string(line, *i, parse);
	}
	parse->in_dollar = FALSE;
}
