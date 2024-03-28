/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:20:20 by marvin            #+#    #+#             */
/*   Updated: 2024/03/21 15:20:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Localiser les sep. (pipe & redirections) < > >> << |
Tout ce qui est entre on met dans le noeud (entiereté de la cmd)
On split ensuite
*/

// t_token	*extract_cmd(t_token **token, char *cmd_line)
// {
// 	size_t	i;
// 	size_t	start;
// 	char	*cmd;
// 	t_token	*new;

// 	i = 0;
// 	new = NULL;
// 	while (cmd_line[i] && cmd_line[i] != '\n')
// 	{
// 		while (cmd_line[i] && cmd_line[i] == 32)
// 			i++;
// 		start = i;
// 		while ((cmd_line[i] && cmd_line[i] != '|'))
// 			i++;
// 		if (i > start)
// 		{
// 			cmd = ft_strndup(cmd_line + start, i - start);
// 			printf("Taille envoyée : %ld\n", i - start);
// 			printf("cmd après strndup : %s\n", cmd);
// 			if (!cmd)
// 				return(perror("Can't get cmd\n"), NULL);
// 			new = init_node(cmd);
// 			if (!new)
// 				return(perror("Can't init my node\n"), free(cmd), NULL);
// 			add_back(token, new);
// 			printf("Contenu de mon noeud : %s\n", new->content);
// 			free(cmd);
// 		}
// 		i++;
// 	}
// 	return (*token);
// }

t_token	*extract_cmd(t_token **token, char *input, char **env)
{
	size_t	i;
	// char	*cmd;
	(void)	env;

	i = 0;
	// cmd = NULL;
	while (input[i])
	{
		// while (input[i] == ' ' || input[i] == '\t')
		// 	i++;
		printf("emplacement du i: %zu\n", i);
		if (input[i] == ' ' || input[i] == '\t')
			i++;
		// else if (input[i] == '"')
		//		tokenize_double_quote(cmd, i, env);
		// else if (input[i] == '\'')
		// 	tokenize_simple_quote( cmd, i);
		else if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			i = tokenize_separator(token, input + i, i, env);
		else
			i = tokenize_arg(token, input, i);
		i++;
	}
	return (*token);
}

// on recupere pas le pipe et le premier char de la seconde cmd
int	tokenize_separator(t_token **token, char *input, int i, char **env)
{
	char *sep;
	t_token *new;
	(void)env;

	new = NULL;
	if (input[i] == '<')
		if (input[i] + 1 == '<')
		{
			sep = ft_strndup(input, 3);
			new = init_node(sep, HERE_DOC);
			add_back(token, new);
			i += 2;
		}
		else
		{
			sep = ft_strndup(input, 2);
			new = init_node(sep, INPUT);
			add_back(token, new);
			i++;
		}

	else if (input[i] == '>')
		if (input[i] + 1 == '>')
		{
			sep = ft_strndup(input, 3);
			new = init_node(sep, APPEND);
			add_back(token, new);
			i += 2;
		}
		else
		{
			sep = ft_strndup(input, 2);
			new = init_node(sep, OUTPUT);
			add_back(token, new);
			i++;
		}
	else if (input[i] == '|')
	{
		sep = ft_strndup(input, 2);
		new = init_node(sep, PIPE);
		add_back(token, new);
		free(sep);
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
	printf("taille de end avant: %d\n", end);
	while(input[end] && input[end] != ' ')
		end++;
	arg = ft_strndup(input + start, end - start);
	new = init_node(arg, ARG);
	add_back(token, new);
	free(arg);
	return (end);
}

// Je crée une str, avec strdup, où je récupère jusqu'au pipe.
// Une fois que j'ai récupéré mon bout de str. je l'envoie pour créer un new node.
// Ensuite je l'envoie dans add_back pour l'ajouter au bout de ma liste chaînée.

