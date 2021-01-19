/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 09:43:56 by alidy             #+#    #+#             */
/*   Updated: 2021/01/19 19:17:23 by alidy            ###   ########lyon.fr   */
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

void    ms_exit_shell(char *str, int exit_status, m_sct *sct)
{
    if (exit_status > 0)
    {
        if (str)
            ft_printf("Minishell: %s : %s", str, strerror(errno));
        else
            ft_printf("Minishell: %s", strerror(errno));
    }
    errno = 0; // a voir
    sct->status = exit_status;
    exit(sct->status);
}

char    *ms_minitrim(char *str)
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

char *ms_get_env(char **env, char *key)
{
    int     i;
    int     len;
    char    *var;

    i = 0;
    var = ft_strjoin(key, "=");
    len = ft_strlen(var);
    while(env[i])
    {
        if (!ft_strncmp(env[i], var, len))
        {
            free(var);
            return (ft_substr(env[i], len, ft_strlen(env[i]) - len));
        }
        i++;
    }
    free(var);
    return (ft_strdup(""));
}

