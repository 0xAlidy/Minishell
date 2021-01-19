/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:22:29 by alidy             #+#    #+#             */
/*   Updated: 2021/01/19 18:33:09 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char    *ft_replace_util(char *s, char *rm, int len_rm, int len_re)
{
    char    *res;
    int     i;
    int     count;

    res = 0;
    i = 0;
    count = 0;
    while (s[i])
    {
        if (!ft_strncmp(s + i, rm, len_rm))
        {
            i += len_rm - 1;
            count++;
        }
        i++;
    }
    if (!(res = malloc(i + 1 - (count * len_rm - len_re))))
        return (0);
    return (res);
}

char    *ft_replace(char *str, char *remove, char *replace, int free)
{
    int     i;
    int     j;
    int     len_rm;
    int     len_re;
    char    *res;

    i = 0;
    j = 0;
    len_rm = ft_strlen(remove);
    len_re = ft_strlen(replace);
    res = ft_replace_util(str, remove, len_rm, len_re);
    while (str[i])
    {
        if (!ft_strncmp(str + i, remove, len_rm))
        {
            ft_memcpy(res + j, replace, len_re);
            i += len_rm;
            j += len_re;
        }
        else
            res[j++] = str[i++];
    }
    res[j] = 0;
    ft_strfree(str, replace, free);
    return (res);
}