/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 09:50:05 by alidy             #+#    #+#             */
/*   Updated: 2021/01/15 12:39:54 by alidy            ###   ########lyon.fr   */
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

m_parse     init_parse()
{
    m_parse parse;

    parse.save = 0;
    parse.content = 0;
    parse.in_input = FALSE;
    parse.in_output = FALSE;
    parse.in_squote = FALSE;
    parse.in_dquote = FALSE;
    parse.in_dollar = FALSE;
    parse.is_double = FALSE;
    return (parse);
}

m_output *new_output(char *output, int is_double)
{
    m_output *new;

    if (!(new = malloc(sizeof(m_output))))
        exit(EXIT_FAILURE);
    new->content = output;
    new->is_double = is_double;
    new->next = 0;
    return (new);
}

m_arg   *new_arg(char *arg)
{
    m_arg *new;

    if (!(new = malloc(sizeof(m_arg))))
        exit(EXIT_FAILURE);
    new->content = arg;
    new->next = 0;
    return (new);
}

m_cmd  *new_command()
{
    m_cmd *command;

    if (!(command = malloc(sizeof(m_cmd))))
        exit(EXIT_FAILURE);
    command->pipe = FALSE;
    command->next = 0;
    return (command);
}

void    debug_struct(m_cmd **cmds)
{
    m_cmd    *temp;
    m_output *out;
    m_arg   *args;

    temp = *cmds;
    if (!*cmds)
        return;
    while (temp->next)
    {
        out = temp->output;
        args = temp->args;
        while (args->next)
        {
            ft_printf("args : %s -> ", args->content);
            args = args->next;
        }
        ft_printf("\n");
        while (out->next)
        {
            ft_printf("out : %s | double = %d -> ", out->content, out->is_double);
            out = out->next;
        }
        ft_printf("\n");
        ft_printf("input: %s",temp->input);
        ft_printf("\n");
        ft_printf("pipe: %d",temp->pipe);
        temp = temp->next;
    }   
}

void    add_command(m_cmd **commands, m_cmd *command)
{
    m_cmd   *temp;

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

void    add_output(char *output, int is_double, m_output **lst)
{
    m_output *new;
    m_output *temp;

    new = new_output(output, is_double);
    temp = *lst;
    if (*lst)
        *lst = new;
    else
    {
        while (temp->next)
            temp = temp->next;
        temp->next = new;
    }
}

void    add_arg(char *content, m_arg **lst)
{
    m_arg *new;
    m_arg *temp;

    new = new_arg(content);
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

int		is_char_printable(int c)
{
	if (c >= 33 && c <= 126)
		return (1);
	return (0);
}

void    create_string(char *line, int i, m_parse *parse, m_env *env)
{
    char *str;
    char *temp;

    str = 0;
    temp = 0;
    if (i - parse->save > 1)  // > 1 ?
    {
        str = ft_substr(line, parse->save, i);
        if (parse->in_dollar == TRUE)
        {
            temp = search_env(str, &env);
            free(str);
            str = temp;
            parse->in_dollar = FALSE;
        }
        ft_strjoin_free(parse->content, str, 2);
    }
    parse->save = i + 2;
}

void    handler_slash(char *line, int *i, m_parse *parse, m_env *env)
{
    if (parse->in_dquote == FALSE && parse->in_squote == FALSE) // sans quotes
    {
        create_string(line, *i - 1, parse, env);
        parse->save = ++(*i);
        if (!is_char_printable(line[*i]))
        {
            ft_printf("Error : multiligne");
            exit(EXIT_FAILURE);
        }
    }
    else if (parse->is_double == TRUE)
    {
        if (line[*i + 1] == '"' || line[*i + 1] == '$' || line[*i + 1] == '\\')
        {
            create_string(line, *i - 1, parse, env);
            (*i)++;
        }
    }
}

void     handler_dollar(char *line, int *i, m_parse *parse, m_env *env)
{
    if (!is_char_printable(line[*i + 1]) || parse->in_squote == TRUE)
        return;
    create_string(line, *i - 1, parse, env);
    parse->in_dollar = TRUE;
    
}

void     handler_quotes(char *line, int *i, m_parse *parse, m_env *env)
{
    if (line[*i] == '"')
        parse->in_squote = TRUE;
    else
        parse->in_dquote = TRUE;
    create_string(line, *i - 1, parse, env);
}

int    set_content(char *line, int i, m_parse *parse, m_cmd *cmd, m_env *env)
{
    parse->save = i;
    while (line[i] && (parse->in_squote == TRUE || parse->in_dquote == TRUE
    || (line[i] != '|' && line[i] != ';' && line[i] != ' ')))
    {
        if (line[i] == '\\')
            handler_slash(line, &i, parse, env);
        else if (line[i] == '\'' || line[i] == '"')
            handler_quotes(line, &i, parse, env);
        else if (line[i] == '$')
            handler_dollar(line, &i, parse, env);
        if (line[i] && (parse->in_squote == TRUE || parse->in_dquote == TRUE
        || (line[i] != '|' && line[i] != ';' && line[i] != ' ')))
            i++;
    }
    if (parse->in_squote == TRUE || parse->in_dquote == TRUE)
    {
        ft_printf("Pas de multiligne"); //ERREUR
        exit(EXIT_FAILURE);
    }
    create_string(line, i, parse, env);
    if (parse->in_input)
        cmd->input = parse->content;
    else if (parse->in_output)
        add_output(parse->content, parse->is_double, &(cmd->output));
    else
        add_arg(parse->content, &(cmd->args));
    parse->in_input = FALSE;
    parse->in_output = FALSE;
    parse->is_double = FALSE;
    return (i);
}

int     set_command(char *line, int i, m_cmd *command, m_env *env)
{
    m_parse parse;

    parse = init_parse();
    while (line[i] && line[i] != '|' && line[i] != ';')
    {
        if (line[i] != '>' || line[i] != '<' || line[i] != ' ') // dans un arg
            i = set_content(line, i, &parse, command, env);
        else if (line[i] == '>' || line[i] == '<') // set redirection
        {
            if (parse.in_output == TRUE || parse.in_input == TRUE) // erreur de type echo < <
            {
                ft_printf("Erreur: redirection");
                exit(EXIT_FAILURE);
            }
            if (line[i] == '>')
            {
                parse.in_output = TRUE;
                if (line[i + 1] == '>')
                {
                    parse.is_double = TRUE;
                    i++;
                }
            }
            else
                parse.in_input = TRUE; 
        }
        i++;
    }
    if (line[i] == '|')
            command->pipe = TRUE;
    return (i);
}

// PROBLEME POINTEUR COMMAND JE PENSE

m_cmd  *set_commands(char *line, m_env *env)
{
    int     i;
    m_cmd   *commands;
    m_cmd   *command;

    i = 0;
    commands = 0;
    while (line[i])
    {
        command = new_command();
        i = set_command(line, i, command, env);
        add_command(&commands, command);
        if (line[i])
            i++;
    }
    debug_struct(&commands);
    return (commands);
}