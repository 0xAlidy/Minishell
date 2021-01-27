/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 09:43:56 by alidy             #+#    #+#             */
/*   Updated: 2021/01/27 15:15:28 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_sct	ms_init_sct(void)
{
	t_sct sct;

	sct.args = 0;
	sct.path = 0;
	sct.status = 0;
	sct.envp = 0;
	sct.saved_stdout = -1;
	sct.saved_stdin = -1;
	sct.saved_cmds = 0;
	return (sct);
}

char	*ms_minitrim(char *s)
{
	int		i;
	char	*res;

	i = 0;
	if (!(res = malloc(ft_strlen(s) + 1)))
		return (0);
	while (s[i])
	{
		if (s[i] == '\t' || s[i] == '\v' || s[i] == '\f' || s[i] == '\r')
			res[i] = ' ';
		else
			res[i] = s[i];
		i++;
	}
	res[i] = 0;
	free(s);
	return (res);
}

char	*ms_current_folder(void)
{
	char	*path;
	char	*res;
	int		i;
	int		len;

	if (!(path = malloc(1024 * sizeof(char))))
		return (0);
	getcwd(path, 1024);
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

void	ms_prompt(t_sct *sct)
{
	char *folder;

	folder = ms_current_folder();
	if (!sct || sct->status != 0)
		ft_printf("\033[0;31m➜\033[0m \033[1;34m%s\033[0m $> ", folder);
	else
		ft_printf("\033[0;32m➜\033[0m \033[1;34m%s\033[0m $> ", folder);
	free(folder);
}

char	*ms_get_env(char **env, char *key)
{
	int		i;
	int		len;
	char	*var;

	i = 0;
	var = ft_strjoin(key, "=");
	len = ft_strlen(var);
	while (env[i])
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
