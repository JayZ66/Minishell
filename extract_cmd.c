/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:07:45 by romlambe          #+#    #+#             */
/*   Updated: 2024/05/06 10:56:10 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*extract_cmd(t_token **token, char *input)
{
	size_t	i;

	i = 0;
	while (input[i])
	{
		while(input[i] == ' ' || input[i] == '\t')
			i++;
		if (!input[i])
			break;
		if (input[i] == ' ' || input[i] == '\t')
			i++;
		else if (ft_strncmp(input + i, ">>", 2) == 0)
			i = tokenize_append(token, input , i);
		else if (ft_strncmp(input + i, ">", 1) == 0)
			i = tokenize_output(token, input, i);
		else if (ft_strncmp(input + i, "<<", 2) == 0)
			i = tokenize_here_doc(token, input, i);
		else if (ft_strncmp(input + i, "<", 1) == 0)
			i = tokenize_input(token, input, i);
		else if (ft_strncmp(input + i, "|", 1) == 0)
			i = tokenize_pipe(token, i);
		else
			i = tokenize_arg(token, input, i);
	}
	return (*token);
}


