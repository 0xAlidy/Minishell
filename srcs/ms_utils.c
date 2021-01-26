/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 09:43:56 by alidy             #+#    #+#             */
/*   Updated: 2021/01/26 21:13:43 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

m_sct   ms_init_sct()
{
    m_sct sct;

    sct.path = 0;
    sct.status = 0;
    sct.envp = 0;
    sct.saved_stdout = -1;
    sct.saved_stdin = -1;
    return (sct);
}

char    *ms_minitrim(char *str)
{
    int     i;
    char    *res;

    i = 0;
    if (!(res = malloc(ft_strlen(str) + 1)))
        return (0);
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
        return (0);
    getcwd(path, PATH_MAX);
	len = ft_strlen(path);
	i = len;
    if (i == 1)
        res = ft_strdup("/");
    else
    {
        while (path[i] != '/')
		    i--;
        res = ft_substr(path, i + 1, len - i);
    }
	free(path);
	return (res);
}

void    ms_prompt(void)
{
    char *folder;

    folder = ms_current_folder();
    ft_printf("\033[1;34m%s\033[0m $> ", folder);
    free(folder);
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

int     ms_indexchr(char *s, int c)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	if (s[i] == c)
		return (i);
	return (-1);
}
