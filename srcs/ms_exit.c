/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 18:41:16 by alidy             #+#    #+#             */
/*   Updated: 2021/01/23 10:58:13 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int    ms_exit_test(char *str)
{
    int i;

    i = 0;
    if (str[i] == '-' || ft_isdigit(str[i]))
        i++;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (FALSE);
        i++;
    }
    return (TRUE);
}
void    ms_exit(m_sct *sct, m_env *env)
{
    int i;
    int res;

    i = 1;
    res = EXIT_SUCCESS;
    while (sct->args[i])
        i++;
    if (i > 2)
    {
        ft_printf("Minishell: exit: too many arguments\n");
        sct->status = 1;
        return;
    }
    if (i == 2)
    {
        if (!ms_exit_test(sct->args[1]))
        {
            ft_printf("Minishell: exit: %s: numeric argument required\n", sct->args[1]);
            return;
        }
        res = ft_atoi(sct->args[1]);
    }
    if (sct->in_pipe == FALSE)
    {
        ms_free_cmd(sct->saved_cmds);
        ms_free_sct(sct);
        ms_free_env(&env);
        ft_printf("exit\n");
    }
    exit(res);
}