/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 08:44:00 by alidy             #+#    #+#             */
/*   Updated: 2021/01/27 15:15:54 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ms_is_char_printable(int c)
{
	if (c >= 33 && c <= 126)
		return (TRUE);
	return (FALSE);
}

char	*ms_create_dollar(char *str, int i, t_parse *parse)
{
	char *res;

	res = 0;
	if (!ft_strncmp(str, "?", 1))
	{
		str = ft_strjoin_free("$", str, 2);
		parse->content = ft_strjoin_free(parse->content, str, 1);
		parse->save = i + 1;
	}
	else
		res = ms_search_env(str, parse->env);
	free(str);
	return (res);
}

void	ms_create_string(char *line, int i, t_parse *parse)
{
	char	*str;
	int		ok;

	ok = FALSE;
	if (!(str = ft_substr(line, parse->save, i - parse->save)))
		return ;
	if (parse->in_dollar == TRUE)
	{
		str = ms_create_dollar(str, i, parse);
		parse->in_dollar = FALSE;
		if (!ft_isalnum(line[i]))
			ok = TRUE;
	}
	parse->content = ft_strjoin_free(parse->content, str, 3);
	if (ok == TRUE)
		parse->save = i;
	else
		parse->save = i + 1;
	if (!str)
		parse->none = TRUE;
}

int		ms_parse_arg(char *l, int i, t_parse *p)
{
	p->save = i;
	while (l[i] && (p->in_squote == TRUE || p->in_dquote == TRUE
	|| p->in_slash == TRUE
	|| (l[i] != '|' && l[i] != ';' && l[i] != ' '
	&& l[i] != '<' && l[i] != '>')))
	{
		p->in_slash = FALSE;
		if (p->in_dollar == TRUE && !ft_isalnum(l[i]))
			ms_create_string(l, i, p);
		if (l[i] == '\\')
		{
			if ((ms_handler_slash(l, &i, p)) == -1)
				return (-1);
		}
		else if (l[i] == '\'' || l[i] == '"')
			ms_handler_quotes(l, &i, p);
		if (l[i] == '$')
			ms_handler_dollar(l, &i, p);
		if (l[i] == ' ' && p->in_dquote == TRUE && p->in_dollar)
			ms_create_string(l, i, p);
		if (l[i] && (p->in_squote == TRUE || p->in_dquote == TRUE ||
		p->in_slash == TRUE || (l[i] != '|' && l[i] != ';' && l[i] != ' ')))
			i++;
	}
	return (i);
}
