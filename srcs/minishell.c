/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 10:54:17 by alidy             #+#    #+#             */
/*   Updated: 2021/01/19 19:17:00 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    minishell(int fd, char **e)
{
    m_cmd   *commands;
    m_env   *env;
    m_sct   sct;
    char    *input;

    env = ms_set_env(e);
    while (42)
    {
        signal(SIGINT, signal_handler);
        //signal(SIGQUIT, SIG_IGN);
        prompt();
        get_next_line(fd, &input);
        input = ms_minitrim(input);
        commands = ms_set_commands(input, env);
        if (commands && commands->args) // s'il y a une commande
        {
            sct = init_sct();
            ms_exec_commands(&sct, &commands, env);
        }
    }
    //free_minishell(env, commands);
    if (fd)
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