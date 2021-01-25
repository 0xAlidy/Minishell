/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 09:50:05 by alidy             #+#    #+#             */
/*   Updated: 2021/01/25 17:02:26 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void		ms_create_string(char *line, int i, m_parse *parse, m_env *env)
{
    char *str;
    char *temp;

    str = 0;
    temp = 0;
    (void)line;
    (void)env;
    //ft_printf("i : %d save : %d content : %s\n", i, parse->save, parse->content);  // debug
    str = ft_substr(line, parse->save, i - parse->save);
    if (parse->in_dollar == TRUE)
    {
        if (!ft_strncmp(str, "?", 1)) // pour gerer $?
        {
            str = ft_strjoin_free("$", str, 2);
            parse->content = ft_strjoin_free(parse->content, str, 1);
            parse->save = i + 1;
            //ft_printf("content after : %s\n", parse->content); // debug
        }
        else
            temp = ms_search_env(str, &env);
        free(str);
        if (!temp)
            return;
        str = temp;
        if (line[i] == '/')
            str = ft_strjoin_free(str, "/", 1);
        parse->in_dollar = FALSE;
    }
    parse->content = ft_strjoin_free(parse->content, str, 3);
    //ft_printf("content after : %s\n", parse->content); // debug
    parse->save = i + 1;
}

int    ms_handler_slash(char *line, int *i, m_parse *parse, m_env *env)
{
    if (line[*i + 1])
        parse->in_slash = TRUE;
    if (parse->in_dquote == FALSE && parse->in_squote == FALSE) // sans quotes
    {
        if (line[*i + 1] == '?')
        {
            ms_create_string(line, *i, parse, env);
            parse->content = ft_strjoin_free(parse->content, "\t", 1);
            parse->save = ++(*i);
        }
        else
        {
            ms_create_string(line, *i, parse, env);
            parse->save = ++(*i);
            if (line[*i] == 0)
                return (ms_free_parse(-1, "backslash", parse));
        }
    }
    else if (parse->in_dquote == TRUE)
    {
        if (line[*i + 1] == '?')
        {
            ms_create_string(line, *i, parse, env);
            parse->content = ft_strjoin_free(parse->content, "\t", 1);
            parse->save = ++(*i);
        }
        else if (line[*i + 1] == '"' || line[*i + 1] == '$' || line[*i + 1] == '\\')
        {
            ms_create_string(line, *i, parse, env);
            (*i)++;
        }
    }
    return (TRUE);
}

void     ms_handler_dollar(char *line, int *i, m_parse *parse, m_env *env)
{
    if (line[*i + 1] == '?' && (parse->in_slash == TRUE || parse->in_squote == TRUE))
    {
        if (parse->in_squote == TRUE)
            ms_create_string(line, *i, parse, env);
        parse->content = ft_strjoin_free(parse->content, "$\t", 1);
        parse->save = *i + 1;
        return;
    }
    if (!ms_is_char_printable(line[*i + 1]) || parse->in_squote == TRUE || line[*i + 1] == '\\' || parse->in_slash == TRUE)
        return;
    ms_create_string(line, *i, parse, env);
    parse->in_dollar = TRUE;
}

void     ms_handler_quotes(char *line, int *i, m_parse *parse, m_env *env)
{
    if (line[*i] == '"' && parse->in_squote == FALSE)
    {
        if (parse->in_dquote == TRUE)
            parse->in_dquote = FALSE;
        else
            parse->in_dquote = TRUE;
        ms_create_string(line, *i, parse, env);
    }
    else if (line[*i] == '\'' && parse->in_dquote == FALSE)
    {
        if (parse->in_squote == TRUE)
            parse->in_squote = FALSE;
        else
            parse->in_squote = TRUE;
        ms_create_string(line, *i, parse, env);
    }
    parse->in_dollar = FALSE;
}

int    ms_set_content(char *line, int i, m_parse *parse, m_cmd *cmd, m_env *env)
{
    parse->save = i;
    while (line[i] && (parse->in_squote == TRUE || parse->in_dquote == TRUE || parse->in_slash == TRUE
    || (line[i] != '|' && line[i] != ';' && line[i] != ' ' && line[i] != '<' && line[i] != '>')))
    {
        parse->in_slash = FALSE;
        if (line[i] == '/' && parse->in_dollar == TRUE)
            ms_create_string(line, i, parse, env);
        if (line[i] == '\\')
        {
            if ((ms_handler_slash(line, &i, parse, env)) == -1)
                return (-1);
        }
        else if (line[i] == '\'' || line[i] == '"')
            ms_handler_quotes(line, &i, parse, env);
        if (line[i] == '$')
            ms_handler_dollar(line, &i, parse, env);
        if (line[i] && (parse->in_squote == TRUE || parse->in_dquote == TRUE || parse->in_slash == TRUE
        || (line[i] != '|' && line[i] != ';' && line[i] != ' ')))
            i++;
    }
    if (parse->in_squote == TRUE || parse->in_dquote == TRUE)
        return (ms_free_parse(-1, "quotes", parse));
    ms_create_string(line, i, parse, env);
    if (parse->type_output)
        ms_add_output(parse->content, parse->type_output, &(cmd->output));
    else
        ms_add_arg(parse->content, &(cmd->args));
    free(parse->content);
    parse->content = 0;
    parse->type_output = 0;
    parse->is_double = FALSE;
    return (i);
}

int     ms_set_command(char *line, int i, m_cmd *command, m_env *env)
{
    m_parse parse;

    parse = ms_init_parse();
    while (line[i] && line[i] != '|' && line[i] != ';')
    {
        if (line[i] != '>' && line[i] != '<' && line[i] != ' ')
            if ((i = ms_set_content(line, i, &parse, command, env)) == -1)
                return (-1);
        if (line[i] == '>' || line[i] == '<')
        {
            if (parse.type_output)
                return (ms_free_parse(-1, "redirection", &parse));
            if (line[i] == '>')
            {
                parse.type_output = 2;
                if (line[i + 1] == '>')
                {
                    parse.type_output = 3;
                    i++;
                }
            }
            else
                parse.type_output = 1; 
        }
        if (line[i] && line[i] != '|' && line[i] != ';')
            i++;
    }
    if (parse.type_output)
        return (ms_free_parse(-1, "redirection", &parse));
    if (line[i] == '|')
    {
        command->pipe = TRUE;
        if (ms_check_pipe(command, line, i + 1))
            return (ms_free_parse(-1, "pipe", &parse));
    }
    return (ms_free_parse(i, 0, &parse));
}

int     ms_free_parse(int res, char *msg, m_parse *parse)
{
    if (parse->content)
        free(parse->content);
    if (msg)
        ft_printf("Minishell: %s: syntax error\n", msg);
    return (res);
}

m_cmd  *ms_set_commands(char *line, m_env *env, m_sct *sct)
{
    int     i;
    m_cmd   *commands;
    m_cmd   *command;

    i = 0;
    commands = 0;
    while (line[i])
    {
        command = ms_new_command();
        if ((i = ms_set_command(line, i, command, env)) == - 1)
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
    return (commands);
}
