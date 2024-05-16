/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:19:14 by jeguerin          #+#    #+#             */
/*   Updated: 2024/05/16 19:35:25 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_isspace(const char *str)
{
    size_t  i;
    size_t  j;

    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] == 32)
            j++;
        i++;
    }
    if (i == j)
        return (1);
    return (0);
}
