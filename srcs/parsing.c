/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 09:50:05 by alidy             #+#    #+#             */
/*   Updated: 2021/01/14 14:13:43 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
/*
 metacharactere : "‘|’, ‘&’, ‘;’, ‘(’, ‘)’, ‘<’, or ‘>’"


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

 \ => desactive " et $, utilise le principe sans quotes qund il est suivi de \ ou seul



 " et \ impaires => message erreur multiligne 
*/


// GERER LE CAS echo >  > ok        ne compter qu'un fichier  echo > mdr salut =====> salut mdr

m_parse     init_parse()
{
    m_parse parse;

    parse.save = 0;
    parse.content = 0;
    parse.start_slash = FALSE;
    parse.in_slash = FALSE;
    parse.in_input = FALSE;
    parse.in_arg = FALSE;
    parse.in_output = FALSE;
    parse.in_squote = FALSE;
    parse.in_dquote = FALSE;
    parse.in_dollar = FALSE;
    parse.is_double = FALSE;
    return (parse);
}

int		is_char_printable(int c)
{
	if (c >= 33 && c <= 126)
		return (1);
	return (0);
}

void    set_flag_slash(char *line, int *i, m_parse *parse)
{
    if (parse->in_slash == FALSE && parse->in_squote == FALSE && parse->in_dquote == FALSE)
    {
        if (!is_char_printable(line[*i + 1]))
        {
            ft_printf("Pas de multiligne"); //ERREUR
            exit(EXIT_FAILURE);
        }
        parse->in_slash = TRUE;
        (*i)++;
    }
}

void     set_flag_quotes(char *line, int i, m_parse *parse)
{
    if (line[i] == '"') 
    {
        if (parse->in_squote == TRUE || parse->in_slash == TRUE)
            return;
        ft_printf("i : %d\n",i);
        if (parse->in_dquote == FALSE)
        {
            parse->in_dquote = TRUE;
            if (parse->in_arg == FALSE)
                parse->save = i;
            parse->in_arg = TRUE;
        }
        else
            parse->in_dquote = FALSE; 
    }   
    else
    {
        if (parse->in_dquote == TRUE || (parse->in_slash == TRUE && parse->in_squote == FALSE))
            return;
        if (parse->in_squote == FALSE)
        {
            parse->in_squote = TRUE;
            if (parse->in_arg == FALSE)
                parse->save = i;
            parse->in_arg = TRUE;
        }
        else
            parse->in_squote = FALSE; 
    }
}

m_output *new_output(char *output, int is_double)
{
    m_output *new;

    if (!(malloc(sizeof(m_output))))
        exit(EXIT_FAILURE);
    new->content = output;
    new->is_double = is_double;
    new->next = 0;
    return (new);
}

m_arg   *new_arg(char *arg)
{
    m_arg *new;

    if (!(malloc(sizeof(m_arg))))
        exit(EXIT_FAILURE);
    new->content = arg;
    new->next = 0;
    return (new);
}

void    add_output(char *output, int is_double, m_cmd *lst)
{
    m_output *new;
    m_output *temp;

    new = new_output(output, is_double);
    temp = lst;
    if (lst)
        lst = new;
    else
    {
        while (temp->next)
            temp = temp->next;
        temp->next = new;
    }
}

char    *add_arg(char *content, m_cmd *lst)
{
    m_arg *new;
    m_arg *temp;

    new = new_arg(content);
    temp = lst;
    if (!lst)
        lst = new;
    else
    {
        while (temp->next)
            temp = temp->next;
        temp->next = new;
    }
}


void    set_command(char *line, int i, m_cmd *command)
{
    m_parse parse;

    parse = init_parse();
    // content qui dup et join au fur et a mesure
    while (line[i] && line[i] != '|' && line[i] != ';')
    {
        if (line[i] == '\\')
            set_flag_slash(line, &i, &parse);
        if (line[i] == '\'' || line[i] == '"')
            set_flag_quotes(line, i, &parse);
        if (parse.in_squote == TRUE || parse.in_dquote == TRUE)
            ;
        else if (parse.in_slash == FALSE && (line[i] == '>' || line[i] == '<'))
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
                else
                    parse.is_double = FALSE;
            }
            else
                parse.in_input = TRUE; 
        }
        else if (line[i] == ' ')
        {
            if (parse.in_arg == TRUE)
            {

                ft_printf("[1] save: %d i: %d %.*s\n", parse.save, i ,i - parse.save, line + parse.save);
                if (parse.in_output == TRUE)
                {
                    add_output(content, parse.is_double, command->output); // ajoute une sortie a la liste commande->output (content = chaine de save a i, is_double = parse.is_double)
                    parse.in_output = FALSE;
                }
                else if (parse.in_input == TRUE)
                {
                    parse.in_input = FALSE;
                    command->input = content; // modifie la valeure de commande->input (content = chaine de save a i)
                }
                else
                    add_arg(content, command->args); // ajouter un argument a ma liste (content = chaine de save a i)
                parse.in_arg = FALSE;
                parse.start_slash = FALSE;
            }
        }
        else
        {
            if (parse.in_arg == FALSE)
            {
                if (parse.in_slash == TRUE)
                    parse.start_slash = TRUE;
                parse.save = i;
                parse.in_arg = TRUE;
            }
        }
        i++;
        parse.in_slash = FALSE;
    }
    if (parse.in_arg == TRUE)
    {
        if (parse.in_dquote || parse.in_squote)
        {
            ft_printf("Error: quotes");
            exit(EXIT_FAILURE);
        }
        if (parse.in_arg == TRUE)
        {
            ft_printf("[1] save: %d i: %d %.*s\n", parse.save, i ,i - parse.save, line + parse.save);
            content = add_arg(line, i, &parse);
            if (parse.in_output == TRUE)
            {
                add_output(content, parse.is_double, command->output); // ajoute une sortie a la liste commande->output (content = chaine de save a i, is_double = parse.is_double)
                parse.in_output = FALSE;
            }
            else if (parse.in_input == TRUE)
            {
                parse.in_input = FALSE;
                command->input = content; // modifie la valeure de commande->input (content = chaine de save a i)
            }
            else
                add_arg(content, command->args); // ajouter un argument a ma liste (content = chaine de save a i)
            parse.in_arg = FALSE;
            parse.start_slash = FALSE;
        }
    }
    if (line[i] == '|')
            command->pipe = TRUE;
    exit(1);
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

void    add_back_command(m_cmd **commands, m_cmd *command) // a regler
{
    m_cmd   *temp;

    temp = *commands;
    if (!temp)
        *commands = command;
    else
    {
        while (temp->next)
            temp = temp->next;
        temp->next = command;
    }
}

m_cmd  *set_commands(char *line)
{
    int     i;
    m_cmd   *commands;
    m_cmd   *command;

    i = 0;
    commands = 0;
    command = new_command();
    while (line[i])
    {
        set_command(line, i, command);
        add_back_command(&commands, command);
        command = new_command();
        if (line[i])
            i++;
    }
    return (commands);
}