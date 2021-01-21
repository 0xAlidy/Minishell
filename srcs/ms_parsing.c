/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 09:50:05 by alidy             #+#    #+#             */
/*   Updated: 2021/01/21 12:12:49 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
/*

 echo "salut mdr $path" 'test'| cat -e > text.txt

 commande : echo
 argument 1 : "salut mdr $path" => "salut mdr /user/alid/minishell"
 argument 2 : 'test'
 operateur : |
 commande : cat
 argument 1 : -e
 operateur : >


 \ => efface la barre et ne prete pas attention au charactere d'apres 
 '' => ecrit exactement ce qu'il y a dedans 
 "" => comme '' sauf qu'il prend en compte

 $ => remplace par une variable d'environnement sauf si c'est un espace apres ou qu'il y a \ avant
 \ => supprime la barre si suivi de " ou de $ sinon la laisse, suit la regle aussi avec les \


 Sans quotes :

 \ => efface la barre et ne prete pas attention au charactere d'apres
 $ => remplace par la valeur env sauf s' il n'y a rien apres , supprime le $ s'il y a des quotes apres

 Simple quotes : ecrit exactement ce qu'il y a dedans
 
 \ => ne fait rien sauf si elle suivi de ' => ferme la quote

 Double quotes: ecrit exactement ce qu'il y a dedans
 
 $ => remplace par la valeur env sauf s' il n'y a rien apres

 \ => desactive " et $ et \ sinon garde le \



 " et \ impaires => message erreur multiligne 
*/

// GERER LE CAS echo >  > ok  ne compter qu'un fichier  echo > mdr salut =====> salut mdr

void    ms_debug_struct(m_cmd **cmds)
{
    m_cmd    *temp;
    m_output *out;
    m_arg   *args;

    temp = *cmds;
    if (!cmds)
        return;
    while (temp)
    {
        out = temp->output;
        args = temp->args;
        ft_printf("args : ");
        while (args)
        {
            ft_printf("%s -> ", args->content);
            args = args->next;
        }
        ft_printf("\n");
        ft_printf("out : ");
        while (out)
        {
            ft_printf("%s [%d] -> ", out->content, out->type);
            out = out->next;
        }
        ft_printf("\n");
        ft_printf("pipe: %d",temp->pipe);
        ft_printf("\n");
        temp = temp->next;
    }   
}

m_parse     ms_init_parse()
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

m_output *ms_new_output(char *output, int type)
{
    m_output *new;

    if (!(new = malloc(sizeof(m_output))))
        exit(EXIT_FAILURE);
    new->content = ft_strdup(output);
    new->type = type;
    new->next = 0;
    return (new);
}

m_arg   *ms_new_arg(char *arg)
{
    m_arg *new;

    if (!(new = malloc(sizeof(m_arg))))
        exit(EXIT_FAILURE);
    new->content = ft_strdup(arg);
    new->next = 0;
    return (new);
}

m_cmd  *ms_new_command()
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

void    ms_add_command(m_cmd **commands, m_cmd *command)
{
    m_cmd   *temp;

    temp = *commands;
    
    if (!*commands)
        *commands =command;
    else
    {
        while (temp->next)
            temp = temp->next;
        temp->next = command;
    }
}

void    ms_add_output(char *output, int type, m_output **lst)
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

void    ms_add_arg(char *content, m_arg **lst)
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

int		ms_is_char_printable(int c)
{
	if (c >= 33 && c <= 126)
		return (1);
	return (0);
}

int     ms_is_empty(char *line, int i)
{
    while (line[i])
    {
        if (ms_is_char_printable(line[i]))
            return (FALSE);
        i++;
    }
    return (TRUE);
}

void    ms_create_string(char *line, int i, m_parse *parse, m_env *env)
{
    char *str;
    char *temp;

    str = 0;
    temp = 0;
    (void)line;
    (void)env;
    //ft_printf("i : %d save : %d content : %s\n", i, parse->save, parse->content);
    if (i - parse->save > 0)  // > 1 ?
    {
        str = ft_substr(line, parse->save, i - parse->save);
        if (parse->in_dollar == TRUE)
        {
            if (!ft_strncmp(str, "?", 1)) // pour gerer $?
            {
                str = ft_strjoin_free("$", str, 2);
                parse->content = ft_strjoin_free(parse->content, str, 1);
            }
            else
                temp = ms_search_env(str, &env);
            free(str);
            if (!temp)
                return;
            str = temp;
            parse->in_dollar = FALSE;
        }
        parse->content = ft_strjoin_free(parse->content, str, 3);
    }
    //ft_printf("content after : %s\n", parse->content);
    parse->save = i + 1;
}

void    ms_handler_slash(char *line, int *i, m_parse *parse, m_env *env)
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
            if (!ms_is_char_printable(line[*i]))
            {
                ft_printf("Error : multiligne");
                exit(EXIT_FAILURE);
            }
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
    if (line[*i] == '"')
    {
        if (parse->in_dquote == TRUE)
            parse->in_dquote = FALSE;
        else
            parse->in_dquote = TRUE;
    }
    else
     {
        if (parse->in_squote == TRUE)
            parse->in_squote = FALSE;
        else
            parse->in_squote = TRUE;
    }
    ms_create_string(line, *i, parse, env);
}

int    ms_set_content(char *line, int i, m_parse *parse, m_cmd *cmd, m_env *env)
{
    parse->save = i;
    while (line[i] && (parse->in_squote == TRUE || parse->in_dquote == TRUE || parse->in_slash == TRUE
    || (line[i] != '|' && line[i] != ';' && line[i] != ' ' && line[i] != '<' && line[i] != '>')))
    {
        parse->in_slash = FALSE;
        if (line[i] == '\\')
            ms_handler_slash(line, &i, parse, env);
        else if (line[i] == '\'' || line[i] == '"')
            ms_handler_quotes(line, &i, parse, env);
        if (line[i] == '$')
            ms_handler_dollar(line, &i, parse, env);
        if (line[i] && (parse->in_squote == TRUE || parse->in_dquote == TRUE || parse->in_slash == TRUE
        || (line[i] != '|' && line[i] != ';' && line[i] != ' ')))
            i++;
    }
    if (parse->in_squote == TRUE || parse->in_dquote == TRUE)
    {
        ft_printf("ERREUR: QUOTES"); //ERREUR
        exit(EXIT_FAILURE);
    }
    ms_create_string(line, i, parse, env);
    if (parse->content)
    {
        if (parse->type_output)
            ms_add_output(parse->content, parse->type_output, &(cmd->output));
        else
            ms_add_arg(parse->content, &(cmd->args));
        free(parse->content);
        parse->content = 0;
        parse->type_output = 0;
        parse->is_double = FALSE;
    }
    return (i);
}

int     ms_set_command(char *line, int i, m_cmd *command, m_env *env)
{
    m_parse parse;

    parse = ms_init_parse();
    while (line[i] && line[i] != '|' && line[i] != ';')
    {
        if (line[i] != '>' && line[i] != '<' && line[i] != ' ') // dans un arg
            i = ms_set_content(line, i, &parse, command, env);
        if (line[i] == '>' || line[i] == '<') // set redirection
        {
            if (parse.type_output) // erreur de type echo < <
            {
                ft_printf("Erreur: redirection");
                exit(EXIT_FAILURE);
            }
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
    {
        ft_printf("ERROR : Redirection");
        exit(EXIT_FAILURE);
    }
    if (line[i] == '|')
    {
        command->pipe = TRUE;
        if (ms_is_empty(line, i + 1))
        {
            ft_printf("ERREUR: pipe : multiligne");
            exit(EXIT_FAILURE);
        }
    }
    if (parse.content)
        free(parse.content);
    return (i);
}

m_cmd  *ms_set_commands(char *line, m_env *env)
{
    int     i;
    m_cmd   *commands;
    m_cmd   *command;

    i = 0;
    commands = 0;
    while (line[i])
    {
        command = ms_new_command();
        i = ms_set_command(line, i, command, env);
        ms_add_command(&commands, command);
        if (line[i])
            i++;
    }
    //ms_debug_struct(&commands);
    return (commands);
}
