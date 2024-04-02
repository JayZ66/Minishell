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
		// i++;
	}
	// *token = clean_arg(token, ARG);
	return (*token);
}

// // on recupere pas le pipe et le premier char de la seconde cmd
int	tokenize_separator(t_token **token, char *input, int i, char **env)
{
	// char *sep;
	t_token *new;
	(void)env;

	new = NULL;
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
	while(input[end] && input[end] != ' '&& input[end] != '\t' && input[end] != '|' && input[end] != '<' && input[end] != '>')
		end++;
	arg = ft_strndup(input + start, end - start);
	printf("arg: %s\n", arg);
	new = init_node(arg, ARG);
	add_back(token, new);
	free(arg);
	if (input[end] == 0)
		return (end);
	else
		return (end + 1);
}

t_token	*clean_arg(t_token **token, Token_type type)
{
	t_token	*temp;

	temp = *token;
	while (temp != NULL)
	{
		if(temp->type == type)
		{
			temp->content = ft_clean_space(temp->content);
		}
		temp = temp->next;
	}
	return(temp);
}

char	*ft_clean_space(char *content)
{
	int		i;
	int		flag;
	char	*temp;

	i = 0;
	flag = 0;
	temp = (char *)malloc(sizeof(char) * (ft_strlen(content) + 1));
	while(content[i] == ' ' || content[i] == '\t')
		i++;
	while (content[i])
	{
		if (content[i] == ' ' || content[i] == '\t')
			flag = 1;
		if (!(content[i] == ' ' || content[i] == '\t'))
		{
			if (flag == 1)
				temp[i] = ' ';
			flag = 0;
			temp[i] = content[i];
		}
		i++;
	}
	temp[i] = 0;
	return (temp);
}

int	tokenize_double_quote(t_token **token, char *input, int i, char **env)
{
	int		start;
	int		end;
	int		count_quote;
	(void)	env;
	char	*arg;
	t_token	*new;

	start = i;
	end = i;
	count_quote = 0;
	while(input[end])
	{
		if (input[end] == '"')
			count_quote++;
		end++;
	}
	if (count_quote % 2 != 0)
	{
		perror("pas de seconde double quote\n");
		exit(EXIT_FAILURE);
	}
	printf("end: %d \n", end);
	arg = ft_strndup(input + start, end - start);
	new = init_node(arg, ARG);
	add_back(token, new);
	free(arg);
	return (end + 1);
}

int	tokenize_simple_quote(t_token **token, char *input, int i)
{
	int		start;
	int		end;
	int		count_quote;
	char	*arg;
	t_token	*new;

	start = i;
	end = i;
	count_quote = 0;
	while(input[end])
	{
		if (input[end] == '\'')
			count_quote++;
		end++;
	}
	if (count_quote % 2 != 0)
	{
		perror("pas de seconde simple quote\n");
		exit(EXIT_FAILURE);
	}
	arg = ft_strndup(input + start, end - start);
	new = init_node(arg, ARG);
	add_back(token, new);
	free(arg);
	return (end + 1);
}

// Je crée une str, avec strdup, où je récupère jusqu'au pipe.
// Une fois que j'ai récupéré mon bout de str. je l'envoie pour créer un new node.
// Ensuite je l'envoie dans add_back pour l'ajouter au bout de ma liste chaînée.

// Node rafinné : char * avec dedans cmd et arg (en retirant un niveau de quote) + pipe.
// Une seule structure avec pipe & cmd. sans stocker le char étoile du pipe. pour faire redirection.
// Type à pipe et le reste à null.
// A la fin de mon parser je free tout mon lexer.
// Expanser tout mettre au chemin absolu !!
