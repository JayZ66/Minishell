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
// changer la ft pour qu'elle gere chaque type de separateur,

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

int	tokenize_append(t_token **token, char *input, int i, char **env)
{
	(void)	env;
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
	while (input[end]!= 0 && input[end] != '<' && input[end] != '|')
	{
		if (input[end] == '>')
			flag++;
		if (flag > 2)
			break;
		end++;
	}
	temp = ft_strndup(input + start, end - start);
	new = init_node(temp, APPEND);
	add_back(token, new);
	return (end);
}

int	tokenize_output(t_token **token, char *input, int i, char **env)
{
	(void)	env;
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
			break;
		end++;
	}
	temp = ft_strndup(input + start, end - start);
	new = init_node(temp, OUTPUT);
	add_back(token, new);
	return (end);
}

int	tokenize_here_doc(t_token **token, char *input, int i, char **env)
{
	(void)	env;
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
			break;
		end++;
	}
	temp = ft_strndup(input + start, end - start);
	new = init_node(temp, HERE_DOC);
	add_back(token, new);
	return (end);
}

int	tokenize_input(t_token **token, char *input, int i, char **env)
{
	(void)	env;
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
			break;
		end++;
	}
	temp = ft_strndup(input + start, end - start);
	new = init_node(temp, INPUT);
	add_back(token, new);
	i = end;
	return (i);
}

int	tokenize_pipe(t_token **token, int i)
{
	t_token	*new;

	new = init_node_separator(PIPE);
	add_back(token, new);
	i++;
	return (i);
}



// se gere en plusieurs fonctions, doit voir si on a des '"" ou '\''
// si c'est le cas on prend pas en compte les separateurs dans les guillemets
// on les prends en compte qu'à partir du moment ou les separateurs ne sont pas dans des guillemets
int tokenize_arg(t_token **token, char *input, int i)
{
	int start;
	int end;
	char *arg;
	t_token *new;
	start = i;
	end = i;
	// int flag = 0;
	// printf("taille de start %d\n", start);
	// printf("taille de end avant: %d\n", end);
	if (input[end] == '"')
	{
		end++;
		while (input[end] || input[end] == '"')
			end++;
	}
	else
		while((input[end] && input[end] != '|' && input[end] != '<' && input[end] != '>'))
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
// Je crée une str, avec strdup, où je récupère jusqu'au pipe.
// Une fois que j'ai récupéré mon bout de str. je l'envoie pour créer un new node.
// Ensuite je l'envoie dans add_back pour l'ajouter au bout de ma liste chaînée.

// Node rafinné : char * avec dedans cmd et arg (en retirant un niveau de quote) + pipe.
// Une seule structure avec pipe & cmd. sans stocker le char étoile du pipe. pour faire redirection.
// Type à pipe et le reste à null.
// A la fin de mon parser je free tout mon lexer.
// Expanser tout mettre au chemin absolu !!



//A FAIRE
//refaire le clean code car surement besoin du type
//revoir le parsing
//faire un strchr pour trouver les separateurs dans input
//s'il y en a pas juste envoyer dans tokenize arg
