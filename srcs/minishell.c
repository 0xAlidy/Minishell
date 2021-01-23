/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 10:54:17 by alidy             #+#    #+#             */
/*   Updated: 2021/01/23 10:39:54 by alidy            ###   ########lyon.fr   */
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
        ms_signal_handler(1);
        ms_prompt();
        if (ms_gnl_eof(fd, &input) == -2)
        {
            ft_printf("exit\n");
            ms_free_env(&env);
            exit(EXIT_SUCCESS);
        }
        input = ms_minitrim(input);
        commands = ms_set_commands(input, env);
        free(input);
        if (commands && commands->args)
        {
            sct = ms_init_sct();
            ms_exec_commands(&sct, &commands, env);
        }
    }
}

int     main(int argc, char **argv, char **env)
{
    (void) argc;
    (void) argv;
    errno = 0;
    minishell(0, env);
    return (0);
}