/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:17:10 by romlambe          #+#    #+#             */
/*   Updated: 2024/04/11 15:55:44 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//Lire le input et reconnaitre si c'est une cmd, un separateur et definir le separateur

t_token	*extract_cmd(t_token **token, char *input, char **env)
{
	size_t	i;
	(void)	env;

	i = 0;
	while (input[i])
	{
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if (!input[i])
			break;
		if (input[i] == ' ' || input[i] == '\t')
			i++;
		else if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			i = tokenize_separator(token, input, i, env);
		else
			i = tokenize_arg(token, input, i);
	}
	return (*token);
}

int	tokenize_separator(t_token **token, char *input, int i, char **env)
{
	t_token	*new;
	char	*temp;
	int		start;
	int		end;

	(void)env;
	new = NULL;
	temp = NULL;
	if (input[i] == '>')
	{
		if (input[i + 1] == '>')
		{
			start = i + 2;
			end = i + 2;
			while (input[i] && input[i] != '>' && input[i] != '<' && input[i] != '|')
				end++;
			temp = ft_strndup(input + start, end - start);
			new = init_node(temp, APPEND);
			i += 2;
		}
		else
		{

			start = i + 1;
			end = i + 1;
			while (input[i] && input[i] != '>' && input[i] != '<' && input[i] != '|')
				end++;
			temp = ft_strndup(input + start, end - start);
			new = init_node(temp, OUTPUT);
			i++;
		}
	}
}

int	tokenize_separator(t_token **token, char *input, int i, char **env)
{
	// char *sep;
	// size_t	size;
	t_token *new;
	(void)env;
	// char	*arg;

	new = NULL;
	// size = 0;
	if (input[i] == '<')
		if (input[i + 1] == '<')
		{
			new = init_node_separator(HERE_DOC);
			add_back(token, new);
			i += 2;
		}
		else
		{
			new = init_node_separator(INPUT);
			add_back(token, new);
			i++;
		}
	else if (input[i] == '>')
		if (input[i + 1] == '>')
		{
			new = init_node_separator(APPEND);
			add_back(token, new);
			i += 2;
		}
		else
		{
			new = init_node_separator(OUTPUT);
			add_back(token, new);
			i++;
		}
	else if (input[i] == '|')
	{
		new = init_node_separator(PIPE);
		add_back(token, new);
		i++;
	}
	return (i);
}

int tokenize_arg(t_token **token, char *input, int i)
{
	int start;
	int end;
	char *arg;
	t_token *new;
	start = i;
	end = i;
	printf("taille de start %d\n", start);
	printf("taille de end avant: %d\n", end);
	while(input[end] && input[end] != '|' && input[end] != '<' && input[end] != '>')
		end++;
	arg = ft_strndup(input + start, end - start);
	printf("arg: %s\n", arg);
	new = init_node(arg, ARG);
	add_back(token, new);
	free(arg);
	if (input[end] == 0)
		return (end);
	else
		return (end);
}
