/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 23:36:59 by alidy             #+#    #+#             */
/*   Updated: 2020/09/07 17:28:04 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
