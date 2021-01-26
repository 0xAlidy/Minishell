/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 13:31:04 by alidy             #+#    #+#             */
/*   Updated: 2021/01/26 11:24:04 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    ms_cd(m_sct *sct, m_env **env)
{
    char *path;
    int     check;

    check = FALSE;
    if (!sct->args[1] || !strncmp(sct->args[1], "~", 2))
    {
        path = ms_search_env("HOME", env);
        if (!path)
        {
            ft_printf("HOME not set\n");
            sct->status = 1;
            return;
        }
        else if (!path[0])
            return;
    }
    else if (sct->args[1][0] == '/')
        path = ft_strdup(sct->args[1]);
    else if (!strncmp(sct->args[1], "-", 2))
    {
        path = ms_search_env("OLDPWD", env);
        check = TRUE;
    }
    else
    {
        if (!(path = malloc(PATH_MAX * sizeof(char))))
        {
            ms_free_sct(sct);
            ms_free_env(env);
            ft_printf("Minishell: memory crash\n");
            ft_printf("exit\n");
            exit(EXIT_FAILURE);
        }
        getcwd(path, PATH_MAX);
        path = ft_strjoin_free(path, "/", 1);
        path = ft_strjoin_free(path, sct->args[1], 1);
    }
    if ((sct->status = chdir(path)) == -1)
    {
        free(path);
        ms_reset_fd(sct, 3);
        ft_printf("Minishell: cd : %s: %s\n", sct->args[1], strerror(errno));
        sct->status = 1;
        return;
    }
    if (check == TRUE)
        ft_printf("%s\n", path);
    ms_modify_env(env, "OLDPWD", ms_search_env("PWD", env));
    free(path);
    if(!(path = malloc(PATH_MAX * sizeof(char))))
    {
            ms_free_sct(sct);
            ms_free_env(env);
            ft_printf("Minishell: memory crash\n");
            ft_printf("exit\n");
            exit(EXIT_FAILURE);
    }
    getcwd(path, PATH_MAX);
    ms_modify_env(env, "PWD", path);
    sct->status = 0;
}