/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 18:41:16 by alidy             #+#    #+#             */
/*   Updated: 2021/01/20 11:19:46 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

ft_exit(m_sct *sct, m_cmd *cmd, m_env *env)
{
    ms_free_sct(sct);
    ms_free_cmd(cmd);
    ms_free_env(&env);
    ft_printf("exit\n");
    exit(EXIT_SUCCESS);
}