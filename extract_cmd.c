/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:07:45 by romlambe          #+#    #+#             */
/*   Updated: 2024/05/05 17:08:01 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*extract_cmd(t_token **token, char *input, char **env)
{
	size_t	i;
	(void)	env;

	i = 0;
	// printf("input i:%c\n", input[i]);
	while (input[i])
	{
		while(input[i] == ' ' || input[i] == '\t')
			i++;
		if (!input[i])
			break;
		if (input[i] == ' ' || input[i] == '\t')
			i++;
		else if (ft_strncmp(input + i, ">>", 2) == 0)
			i = tokenize_append(token, input , i, env);
		else if (ft_strncmp(input + i, ">", 1) == 0)
			i = tokenize_output(token, input, i, env);
		else if (ft_strncmp(input + i, "<<", 2) == 0)
			i = tokenize_here_doc(token, input, i, env);
		else if (ft_strncmp(input + i, "<", 1) == 0)
			i = tokenize_input(token, input, i, env);
		else if (ft_strncmp(input + i, "|", 1) == 0)
			i = tokenize_pipe(token, i);
		else
			i = tokenize_arg(token, input, i);
		// else
		// 	i++;
	}
	return (*token);
}


