/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 10:54:17 by alidy             #+#    #+#             */
/*   Updated: 2021/01/17 11:30:00 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

m_sct   init_sct()
{
    m_sct sct;

    sct.status = 0;
    return (sct);
}    

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

void    minishell(int fd, char **e)
{
    m_cmd   *commands;
    m_env   *env;
    m_sct   sct;
    char    *input;

    env = set_env(e);
    while (42)
    {
        signal(SIGINT, signal_handler);
        signal(SIGQUIT, SIG_IGN);
        prompt();
        get_next_line(fd, &input);
        commands = set_commands(input, env);
        if (commands && commands->args) // s'il y a une commande
        {
            sct = init_sct();
            ft_printf("exec");
            //exec_commands(sct, commands, env);
        }
    }
    //free_minishell(env, commands);
    close(fd);
}

int     main(int argc, char **argv, char **env)
{
    int fd;

    fd = 0;
    errno = 0;
    if (argc == 1)
        minishell(fd, env);
    else
    {
        if ((fd = open(argv[1], O_RDONLY)) < 0)
            ft_printf("Minishell: %s: %s\n", argv[1], strerror(errno));
        else
            minishell(fd, env);
    }
    return (0);
}