/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:37:39 by alidy             #+#    #+#             */
/*   Updated: 2021/01/27 15:16:17 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ms_debug_struct(t_cmd **cmds)
{
    t_cmd		*temp;
    t_output	*out;
    t_arg		*args;

    temp = *cmds;
    if (!cmds)
        return;
    while (temp)
    {
        out = temp->output;
        args = temp->args;
        ft_printf("args : ");
        while (args)
        {
            ft_printf("%s->", args->content);
            args = args->next;
        }
        ft_printf("\nout : ");
        while (out)
        {
            ft_printf("%s [%d] -> ", out->content, out->type);
            out = out->next;
        }
        ft_printf("\npipe: %d\n",temp->pipe);
        temp = temp->next;
    }   
}

void    ms_print_tab(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
    {
        ft_printf("%s\n", tab[i]);
        i++;
    }
}
