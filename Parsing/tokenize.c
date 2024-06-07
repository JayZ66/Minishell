/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:06:45 by romlambe          #+#    #+#             */
/*   Updated: 2024/06/07 11:22:37 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	tokenize_append(t_token **token, char *input, int i)
{
	t_token	*new;
	int		start;
	int		end;
	char	*temp;
	int		flag;

	start = i;
	end = i;
	new = NULL;
	temp = NULL;
	flag = 0;
	while (input[end] != 0 && input[end] != '<' && input[end] != '|')
	{
		if (input[end] == '>')
			flag++;
		if (flag > 2)
			break ;
		end++;
	}
	temp = ft_strndup(input + start, end - start);
	new = init_node(temp, APPEND);
	add_back(token, new);
	return (end);
}

int	tokenize_output(t_token **token, char *input, int i)
{
	t_token	*new;
	int		start;
	int		end;
	char	*temp;
	int		flag;

	new = NULL;
	temp = NULL;
	start = i;
	end = i;
	flag = 0;
	while (input[end] && input[end] != '<' && input[end] != '|')
	{
		if (input[end] == '>')
			flag++;
		if (flag > 1)
			break ;
		end++;
	}
	temp = ft_strndup(input + start, end - start);
	new = init_node(temp, OUTPUT);
	add_back(token, new);
	return (end);
}

int	tokenize_here_doc(t_token **token, char *input, int i)
{
	t_token	*new;
	int		start;
	int		end;
	char	*temp;
	int		flag;

	new = NULL;
	temp = NULL;
	start = i;
	end = i;
	flag = 0;
	while (input[end] && input[end] != '>' && input[end] != '|')
	{
		if (input[end] == '<')
			flag++;
		if (flag > 2)
			break ;
		end++;
	}
	temp = ft_strndup(input + start, end - start);
	new = init_node(temp, HERE_DOC);
	add_back(token, new);
	return (end);
}

int	tokenize_input(t_token **token, char *input, int i)
{
	t_token	*new;
	int		start;
	int		end;
	char	*temp;
	int		flag;

	new = NULL;
	temp = NULL;
	start = i;
	end = i;
	flag = 0;
	while (input[end] && input[end] != '>' && input[end] != '|')
	{
		if (input[end] == '<')
			flag++;
		if (flag > 1)
			break ;
		end++;
	}
	temp = ft_strndup(input + start, end - start);
	new = init_node(temp, INPUT);
	add_back(token, new);
	i = end;
	return (i);
}
