/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 13:31:04 by alidy             #+#    #+#             */
/*   Updated: 2021/01/26 22:11:47 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ms_set_path(m_sct *sct, m_env **env, char *path, char *var)
{
	path = ms_search_env(var, env);
	if (!path)
	{
		ft_printf("Minishell: %s not set\n", var);
		sct->status = 1;
		return (FALSE);
	}
	else if (!path[0])
		return (FALSE);
	return (TRUE);
}

void	ms_cd_end(m_sct *sct, m_env **env, char *path, int check)
{
	if ((sct->status = chdir(path)) == -1)
	{
		free(path);
		ms_reset_fd(sct, 3);
		ft_printf("Minishell: cd : %s: %s\n", sct->args[1], strerror(errno));
		sct->status = 1;
		return ;
	}
	if (check == TRUE)
		ft_printf("%s\n", path);
	ms_modify_env(env, "OLDPWD", ms_search_env("PWD", env));
	free(path);
	if (!(path = malloc(PATH_MAX * sizeof(char))))
		return ;
	getcwd(path, PATH_MAX);
	ms_modify_env(env, "PWD", path);
	sct->status = 0;
}

void	ms_cd(m_sct *sct, m_env **env)
{
    char	*path;
    int		check;

	check = FALSE;
	path = 0;
	if (!sct->args[1] || !strncmp(sct->args[1], "~", 2))
	{
		if (!ms_set_path(sct, env, path, "HOME"))
			return ;
	}
	else if (sct->args[1][0] == '/')
		path = ft_strdup(sct->args[1]);
	else if (!strncmp(sct->args[1], "-", 2))
	{
		if (!ms_set_path(sct, env, path, "OLDPWD"))
			return ;
		check = TRUE;
	}
	else
	{
		if (!(path = malloc(PATH_MAX * sizeof(char))))
			return ;
		getcwd(path, PATH_MAX);
		path = ft_strjoin_free(path, "/", 1);
		path = ft_strjoin_free(path, sct->args[1], 1);
	}
    ms_cd_end(sct, env, path, check);
}