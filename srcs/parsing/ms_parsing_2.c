/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 08:44:00 by alidy             #+#    #+#             */
/*   Updated: 2021/01/26 18:03:46 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int			ms_is_char_printable(int c)
{
	if (c >= 33 && c <= 126)
		return (TRUE);
	return (FALSE);
}

char	*ms_create_dollar(char *str, int i, m_parse *parse)
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

void	ms_create_string(char *line, int i, m_parse *parse)
{
	char 	*str;
	int		ok;

	ok = FALSE;
	if (!(str = ft_substr(line, parse->save, i - parse->save)))
		return;	
	//ft_printf("str:%s$\n", str);
	//ft_printf("content:%s$\n", parse->content);
	if (parse->in_dollar == TRUE)
	{
		str = ms_create_dollar(str, i, parse);
		parse->in_dollar = FALSE;
		if (!ft_isalnum(line[i]))
			ok = TRUE;
	}
	parse->content = ft_strjoin_free(parse->content, str, 3);
	//ft_printf("content after:%s$\n", parse->content);
	if (ok == TRUE)
		parse->save = i;
	else
		parse->save = i + 1;
	if (!str)
		parse->none = TRUE;
}

int		ms_parse_arg(char *line, int i, m_parse *parse)
{
	parse->save = i;
	while (line[i] && (parse->in_squote == TRUE || parse->in_dquote == TRUE
	|| parse->in_slash == TRUE
	|| (line[i] != '|' && line[i] != ';' && line[i] != ' '
	&& line[i] != '<' && line[i] != '>')))
	{
		parse->in_slash = FALSE;
		if (parse->in_dollar == TRUE && !ft_isalnum(line[i]))
			ms_create_string(line, i, parse);
		if (line[i] == '\\')
		{
			if ((ms_handler_slash(line, &i, parse)) == -1)
				return (-1);
		}
		else if (line[i] == '\'' || line[i] == '"')
			ms_handler_quotes(line, &i, parse);
		if (line[i] == '$')
			ms_handler_dollar(line, &i, parse);
		if (line[i] == ' ' && parse->in_dquote == TRUE && parse->in_dollar)
			ms_create_string(line, i, parse);
		if (line[i] && (parse->in_squote == TRUE || parse->in_dquote == TRUE
		|| parse->in_slash == TRUE
		|| (line[i] != '|' && line[i] != ';' && line[i] != ' ')))
			i++;
	}
	return (i);
}
