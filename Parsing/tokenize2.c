/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:53:50 by romlambe          #+#    #+#             */
/*   Updated: 2024/06/07 11:22:53 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	tokenize_pipe(t_token **token, int i)
{
	t_token	*new;

	new = init_node_separator(PIPE);
	add_back(token, new);
	i++;
	return (i);
}

int	tokenize_arg(t_token **token, char *input, int i, t_sm handle_quote)
{
	int		start;
	int		end;
	char	*arg;
	t_token	*new;

	start = i;
	end = i;
	while (input[end])
	{
		set_quotes_state(input, end, &handle_quote);
		if (handle_quote == reg && (input[end] == '>'
				|| input[end] == '<' || input[end] == '|'))
			break ;
		end++;
	}
	arg = ft_strndup(input + start, end - start);
	new = init_node(arg, CMD);
	add_back(token, new);
	return (end);
}
