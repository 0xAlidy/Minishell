/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 14:38:23 by alidy             #+#    #+#             */
/*   Updated: 2021/01/27 15:16:17 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ms_test_path(char *path, t_sct *sct)
{
	struct stat buf;

	if (stat(path, &buf) == 0)
	{
		if (S_ISDIR(buf.st_mode))
		{
			if (sct->args[0][0] != 0)
				ft_printf("Minishell: %s: is a directory\n", path);
			sct->status = 126;
			return (-1);
		}
		if (S_ISREG(buf.st_mode))
			return (TRUE);
	}
	return (FALSE);
}

char	*ms_search_path(t_sct *sct)
{
	int		i;
	int		save;
	char	*current_path;

	i = 0;
	while (sct->path[i])
	{
		save = i;
		while (sct->path[i] && sct->path[i] != ':')
			i++;
		current_path = ft_substr(sct->path, save, i - save);
		if (sct->path[i - 1] != '/')
			current_path = ft_strjoin_free(current_path, "/", 1);
		current_path = ft_strjoin_free(current_path, sct->args[0], 1);
		if (ms_test_path(current_path, sct) != TRUE)
			free(current_path);
		else
		{
			free(sct->path);
			return (current_path);
		}
		if (sct->path[i])
			i++;
	}
	return (0);
}

void	ms_set_envp(t_sct *sct, t_env **env)
{
	int		len;
	t_env	*temp;

	temp = *env;
	len = 0;
	while (temp)
	{
		len++;
		temp = temp->next;
	}
	if (!(sct->envp = malloc((len + 1) * sizeof(char *))))
		exit(EXIT_FAILURE);
	sct->envp[len] = 0;
	temp = *env;
	len = 0;
	while (temp)
	{
		sct->envp[len] = ft_strdup(temp->name);
		sct->envp[len] = ft_strjoin_free(sct->envp[len], "=", 1);
		sct->envp[len] = ft_strjoin_free(sct->envp[len], temp->content, 1);
		len++;
		temp = temp->next;
	}
}

void	ms_transfort_args(t_sct *sct, t_arg **args)
{
	int		len;
	t_arg	*t;

	t = *args;
	len = 0;
	while (t)
	{
		len++;
		t = t->next;
	}
	if (!(sct->args = malloc((len + 1) * sizeof(char *))))
		exit(EXIT_FAILURE);
	sct->args[len] = 0;
	t = *args;
	len = 0;
	while (t)
	{
		t->content = ft_replace(t->content, "$?", ft_itoa(sct->status), 1);
		t->content = ft_replace(t->content, "\t", "", 1);
		sct->args[len] = ft_strdup(t->content);
		len++;
		t = t->next;
	}
}

int		ms_handler_builtin(t_sct *sct, t_env *env)
{
	if (!ft_strncmp(sct->args[0], "echo", 5))
		ms_echo(sct);
	else if (!ft_strncmp(sct->args[0], "pwd", 4))
		ms_pwd(sct);
	else if (!ft_strncmp(sct->args[0], "env", 4))
		ms_env(sct);
	else if (!ft_strncmp(sct->args[0], "export", 7))
		ms_export(sct, &env);
	else if (!ft_strncmp(sct->args[0], "unset", 6))
		ms_unset(sct, &env);
	else if (!ft_strncmp(sct->args[0], "cd", 3))
		ms_cd(sct, &env);
	else if (!ft_strncmp(sct->args[0], "exit", 5))
		ms_exit(sct, env);
	else
		return (FALSE);
	return (TRUE);
}
