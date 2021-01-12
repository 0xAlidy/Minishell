/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 10:54:17 by alidy             #+#    #+#             */
/*   Updated: 2021/01/12 12:57:49 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char    *ms_current_folder(void)
{
    char	*path;
	char	*res;
    int		i;
	int		len;

    if(!(path = malloc(PATH_MAX * sizeof(char))))
    {
        ft_printf("[ERROR] MALLOC");
        exit(EXIT_FAILURE);
    }
    getcwd(path, PATH_MAX);
	len = ft_strlen(path);
	i = len;
	while (i > 0 && path[i] != '/')
		i--;
    if (i == 0)
        res = ft_strdup("/");
    else
	    res = ft_substr(path, i + 1, len - i);
	free(path);
	return (res);
}

void    prompt(void)
{
    char *folder;

    folder = ms_current_folder();
    ft_printf("\033[1;34m%s\033[0m $> ", folder);
    free(folder);
}

void    signal_handler(int signum)
{
    if (signum == SIGINT)
    {
        ft_printf("\n");
        prompt();
    }
}

int main(int argc, char **argv, char **env)
{
    int res;
    char *input;
    m_cmd *commands;
    errno = 0;
    (void)argc;
    (void)argv;
    signal(SIGINT, signal_handler); // ctrl-c ne me fait pas quitter minishell
    signal(SIGQUIT, SIG_IGN); // ctrl-\ ne me fait pas quitter minishell
    while(1)
    {
        prompt();
        res = get_next_line(0, &input); // exit si ctrl-D a integrer dans le gnl
        commands = set_commands(input);
        if (res == 0 && !strcmp(input, ""))
            exit(EXIT_SUCCESS);
        else if (!strcmp(input, "exit"))
            exit(EXIT_SUCCESS);
        else if (!strcmp(input, "env"))
        {
            int i = 0;
            while(env[i])
            {
                ft_printf("%s\n", env[i]);
                i++;
            }
        }
        // si built-in lancer mon ficher
        // sinon fork+execve avec recherche de la commande dans les fichiers $PATH
    }
}