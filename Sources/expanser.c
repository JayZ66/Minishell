/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:01:08 by marvin            #+#    #+#             */
/*   Updated: 2024/04/19 12:01:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
UNDERSTAND HOW TO MANAGE QUOTES
*/
char *clean_quote(char *input)
{
    int i;
    int tmp;

    i = 0;
    tmp = 0;
    while (input[i])
    {
        if (input[i] == '"' && ft_strnchr(input + i + 1, '"'))
        {
            tmp = i + 1 + ft_strnchr(input + i + 1, '"');
            input = ft_strjoin(ft_strjoin(ft_substr(input, 0, i), ft_substr(input, i + 1, ft_strnchr(input + i + 1, '"'))),
            ft_substr(input + 1, ft_strnchr(input + i + 1, '"') + i + 1, ft_strlen(input)));
            i = tmp - 2;
        }
        else if (input[i] == 39 && ft_strnchr(input + i + 1, 39))
        {
            tmp = i + 1 + ft_strnchr(input + i + 1, 39);
            input = ft_strjoin(ft_strjoin(ft_substr(input, 0, i), ft_substr(input, i + 1, ft_strnchr(input + i + 1, 39))),
            ft_substr(input + 1, ft_strnchr(input + i + 1, 39) + i + 1, ft_strlen(input)));
            i = tmp - 2;
        }
        i++;
    }
    return (input);
}