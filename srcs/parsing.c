/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 09:50:05 by alidy             #+#    #+#             */
/*   Updated: 2021/01/11 14:36:18 by alidy            ###   ########lyon.fr   */
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

t_cmd  *new_command()
{
    t_cmd *command;

    if (!(command = malloc(sizeof(t_cmd))))
        exit(EXIT_FAILURE);
    command->db_redi = FALSE;
    command->pipe = FALSE;
    return (command);
}

int     parsing_command(char *line, int i, t_cmd *command) // check erreurs de quotes et initialise les tableaux
{
    int     squote;
    int     dquote;
    int     word;
    int     args;
    int     output;

    squote = FALSE;
    dquote = FALSE;
    word = FALSE;
    args = 0;
    output = 0;
    while (line[i] && (squote == TRUE || dquote == TRUE || (line[i] != '|' && line[i] != ';')))
    {
        if (squote == TRUE || dquote == TRUE)
        {
            if (line[i] == '\'')
                squote = FALSE;           
            else if (line[i] == '"' && line[i - 1] != '\\')
                dquote = FALSE;
        }
        else if (line[i] == '\'' && (i == 0 || line[i - 1] != '\\'))
                squote = TRUE;           
        else if (line[i] == '"' && (i == 0 || line[i - 1] != '\\'))
                dquote = TRUE;
        else if (line[i] == '>')
        {
            if (line[i + 1] == '>')
            {
                command->db_redi = TRUE;
                i++;
            }
            else
                command->db_redi = FALSE;
            output++;
        }
        else if (line[i] == ' ')
        {
            if (word == TRUE)
                args++;
            word = FALSE;
        }
        else
            word = TRUE;
        i++;
    }
    if (word == TRUE)
        args++;
    if (squote == TRUE || dquote == TRUE) // Nombre de quotes impaires
    {
        ft_printf("Quotes incomplets, multiline off");
        exit(EXIT_FAILURE);
    }
    ft_printf("%d\n", command->pipe);
    if (line[i] == '|')
            command->pipe = TRUE;
    ft_printf("%d", command->pipe);
    if (!(command->args = malloc(args * sizeof(char))))
        exit(EXIT_FAILURE);
    if (!(command->output = malloc(output * sizeof(char))))
        exit(EXIT_FAILURE);
    ft_printf("nb_args: %d  nb_output: %d  double: %d  pipe: %d",args , output, command->db_redi, command->pipe);
    return (i);
}

t_cmd  *tokenizer_input(char *line)
{
    int     i;
    t_cmd   *commands;
    t_cmd   *command;

    i = 0;
    command = new_command();
    commands = command;
    while (line[i])
    {
        i = parsing_command(line, i, command);
        exit(1);
        while (line[i] && line[i] != '|' && line[i] != ';') // complete les commands
        {
            if (line[i] == '<' || line[i] == '>')
            {
                
                
            }
            i++;
        }
        //add_back_command(commands, command);
        command = new_command();
        i++;
    }
    return (commands);
}

