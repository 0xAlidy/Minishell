/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 10:54:17 by alidy             #+#    #+#             */
/*   Updated: 2021/01/19 18:38:33 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

m_sct   init_sct()
{
    m_sct sct;

    sct.status = 0;
    sct.saved_stdout = -1;
    sct.saved_stdin = -1;
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

char    *ft_minitrim(char *str)
{
    int     i;
    char    *res;

    i = 0;
    if (!(res = malloc(ft_strlen(str) + 1)))
    {
        ft_printf("error malloc");
        exit(EXIT_FAILURE);
    }
    while (str[i])
    {
        if (str[i] == '\t' || str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
            res[i] = ' ';
        else
            res[i] = str[i];
        i++;
    }
    res[i] = 0;
    free(str);
    return (res);
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
        //signal(SIGQUIT, SIG_IGN);
        prompt();
        get_next_line(fd, &input);
        input = ft_minitrim(input);
        commands = set_commands(input, env);
        if (commands && commands->args) // s'il y a une commande
        {
            sct = init_sct();
            exec_commands(&sct, &commands, env);
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