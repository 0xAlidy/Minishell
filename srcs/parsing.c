/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 09:50:05 by alidy             #+#    #+#             */
/*   Updated: 2021/01/12 13:55:13 by alidy            ###   ########lyon.fr   */
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
 $ => remplace par la valeur env sauf s' il n'y a rien apres 

 Simple quotes : ecrit exactement ce qu'il y a dedans
 
 \ => ne fait rien sauf si elle suivi de ' => ferme la quote

 Double quotes: ecrit exactement ce qu'il y a dedans
 
 $ => remplace par la valeur env sauf s' il n'y a rien apres

 \ => desactive " et $, utilise le principe sans quotes qund il est suivi de \ ou seul



 " et \ impaires => message erreur multiligne 
*/


// GERER LE CAS echo >  > ok        ne compter qu'un fichier  echo > mdr salut =====> salut mdr


/*
void handler_quotes(char *line, int *i, m_parse *parse, m_cmd *command)
{
    int save;
    int is_s;

    save = *i;
    is_s = (line[*i] == '\'') ? TRUE : FALSE;
    (*i)++;
    while (line[*i] && ((is_s == TRUE && line[*i] != '\'') || (is_s == FALSE && line[*i] != '"')))
    {
        if (is_s == FALSE && line[*i] == '\\')
            (*i)++;
        (*i)++;
    }
    if (!line[*i]) // Nombre de quotes impaires
    {
        ft_printf("Quotes incomplets, multiline off");
        exit(EXIT_FAILURE);
    }
    if (*i - save > 1)
        *in_arg = TRUE;
}

void    handler_slash(char *line, int *i, m_parse *parse)
{
    if (parse->in_slash == FALSE)
    {
        if (!ft_isprint(line[*i + 1]))
        {
            ft_printf("Pas de multiligne"); //ERREUR
            exit(EXIT_FAILURE);
        }
        parse->in_slash = TRUE;
        (*i)++;
    }
}

m_parse     init_parse()
{
    m_parse parse;

    parse.save = 0;
    parse.in_slash = FALSE;
    parse.in_input = FALSE;
    parse.in_arg = FALSE;
    parse.in_output = FALSE;
    parse.in_quote = FALSE;
    parse.is_double = FALSE;
    return (parse);
}

int    set_command(char *line, int i, m_cmd *command)
{
    m_parse parse;

    parse = init_parse();
    while (line[i] && line[i] != '|' && line[i] != ';')
    {
        if (line[i] == '\\')
            handler_slash(line, &i, &parse); 
        if (parse.in_slash == FALSE && (line[i] == '\'' || line[i] == '"'))
            handler_quotes(line, &i, &parse, command);     
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
                if (parse.in_output == TRUE)
                {
                    add_output(command); // ajoute une sortie a la liste commande->output (content = chaine de save a i, is_double = parse.is_double)
                    parse.in_output = FALSE;
                }
                else if (parse.in_input == TRUE)
                {
                    parse.in_input = FALSE;
                    add_input(command); // modifie la valeure de commande->input (content = chaine de save a i)
                }
                else
                    add_arg(command); // ajouter un argument a ma liste (content = chaine de save a i)
                parse.in_arg = FALSE;
            }
        }
        else
        {
            if (parse.in_arg == FALSE)
            {
                parse.save = i;
                parse.in_arg = TRUE;
            }
        }
        i++;
        parse.in_slash = FALSE;
    }
    if (parse.in_arg == TRUE)
    {
        if (parse.in_output == TRUE)
            parse.output++;
        else if (parse.in_input == FALSE)
            parse.args++;
    }
    if (line[i] == '|')
            command->pipe = TRUE;
    if (!(command->args = malloc(args * sizeof(char))))
        exit(EXIT_FAILURE);
    if (!(command->output = malloc(output * sizeof(char))))
        exit(EXIT_FAILURE);
    return(i);
}
*/
m_cmd  *new_command()
{
    m_cmd *command;

    if (!(command = malloc(sizeof(m_cmd))))
        exit(EXIT_FAILURE);
    command->pipe = FALSE;
    command->next = 0;
    return (command);
}

void    add_back_command(m_cmd *commands, m_cmd *command) // a regler
{
    m_cmd   *temp;

    temp = commands;
    if (!commands)
        commands = command;
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
        i = parsing_command(line, i, command);
        add_back_command(commands, command);
        command = new_command();
        if (line[i])
            i++;
    }
    return (commands);
}