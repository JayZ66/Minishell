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

// t_token	*extract_cmd(t_token **token, char *input, char **env)
// {
// 	size_t	i;
// 	(void)	env;

// 	i = 0;
// 	while (input[i])
// 	{
// 		while (input[i] == ' ' || input[i] == '\t')
// 			i++;
// 		if (!input[i])
// 			break;
// 		if (input[i] == ' ' || input[i] == '\t')
// 			i++;
// 		else if (input[i] == '|' || input[i] == '<' || input[i] == '>')
// 			i = tokenize_separator(token, input, i, env);
// 		else
// 			i = tokenize_arg(token, input, i);
// 	}
// 	if (!*token)
// 		return (NULL);
// 	return (*token);
// }

// int	tokenize_separator(t_token **token, char *input, int i, char **env)
// {
// 	t_token	*new;
// 	char	*temp;
// 	int		start;
// 	int		end;

// 	(void)env;
// 	new = NULL;
// 	temp = NULL;
// 	start = 0;
// 	end = 0;
// 	printf("index i: %d\n", i);
// 	if (ft_strncmp(input + i, ">>", 2))
// 	{

// 		start = i;
// 		end = i;
// 		while (input[end]  && input[end] != '<' && input[end] != '|')
// 			end++;
// 		temp = ft_strndup(input + start, end - start);
// 		new = init_node(temp, APPEND);
// 		add_back(token, new);
// 		i = end ;
// 	}
// 	else if (ft_strncmp(input + i, ">", 1))
// 	{
// 		start = i;
// 		end = i;
// 		while (input[end] && input[end] != '<' && input[end] != '|')
// 			end++;
// 		temp = ft_strndup(input + start, end - start);
// 		new = init_node(temp, OUTPUT);
// 		add_back(token, new);
// 		i = end;
// 	}
	// else if (input[i] == '<')
	// {
	// 	if (input[i + 1] == '<')
	// 	{
	// 		new = init_node_separator(APPEND);
	// 		add_back(token, new);
	// 		i += 2;
	// 	}
	// 	else
	// 	{
	// 		new = init_node_separator(OUTPUT);
	// 		add_back(token, new);
	// 		i++;
	// 	}
	// }
	// else if (input[i] == '|')
	// {
	// 	new = init_node_separator(PIPE);
	// 	add_back(token, new);
	// 	i++;
	// }
	// i++;
// 	return (i);
// }


// // on recupere pas le pipe et le premier char de la seconde cmd
// pb avec les types mis (ca doit venir de tokenize arg et de mon i qui doit mal etre implementer)
// int	tokenize_separator(t_token **token, char *input, int i, char **env)
// {
// 	t_token	*new;
// 	char	*temp;
// 	int		start;
// 	int		end;

// 	(void)env;
// 	new = NULL;
// 	temp = NULL;
// 	start = 0;
// 	end = 0;
// 	if (input[i] == '>')
// 	{
// 		if (input[i + 1] == '>')
// 		{
// 			start = i;
// 			end = i;
// 			while (input[end]  && input[end] != '<' && input[end] != '|')
// 				end++;
// 			temp = ft_strndup(input + start, end - start);
// 			new = init_node(temp, APPEND);
// 			add_back(token, new);
// 			i = end ;
// 		}
// 		else
// 		{
// 			start = i;
// 			end = i;
// 			while (input[end] && input[end] != '<' && input[end] != '|')
// 				end++;
// 			temp = ft_strndup(input + start, end - start);
// 			new = init_node(temp, OUTPUT);
// 			add_back(token, new);
// 			i = end;
// 		}
// 	}
// 	else if (input[i] == '<')
// 	{
// 		if (input[i + 1] == '<')
// 		{
// 			new = init_node_separator(APPEND);
// 			add_back(token, new);
// 			i += 2;
// 		}
// 		else
// 		{
// 			new = init_node_separator(OUTPUT);
// 			add_back(token, new);
// 			i++;
// 		}
// 	}
// 	else if (input[i] == '|')
// 	{
// 		new = init_node_separator(PIPE);
// 		add_back(token, new);
// 		i++;
// 	}
// 	i++;
// 	return (i);
// }


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
	while((input[end] && input[end] != '|' && input[end] != '<' && input[end] != '>'))
	{
		// if (input[end] == '"')
		// 	flag ++;
		end++;
	}
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

// int tokenize_arg(t_token **token, char *input, int i)
// {
// 	int start;
// 	int end;
// 	char *arg;

// 	t_token *new;
// 	start = i;
// 	end = i;
// 	printf("taille de start %d\n", start);
// 	printf("taille de end avant: %d\n", end);
// 	while(input[end] && input[end] != '|' && input[end] != '>')
// 		end++;
// 	printf("input[end - 1]: %c\n", input[end - 1]);
// 	if (input[end - 1] == '<')
// 	{
// 		arg = ft_strndup(input + start, end - start);
// 		printf("arg: %s\n", arg);
// 		new = init_node(arg, INPUT);
// 		add_back(token, new);
// 	}
// 	else
// 	{
// 		arg = ft_strndup(input + start, end - start);
// 		printf("arg: %s\n", arg);
// 		new = init_node(arg, ARG);
// 		add_back(token, new);
// 	}
// 	free(arg);
// 	return (end);
// }




// int tokenize_arg(t_token **token, char *input, int i)
// {
// 	int start;
// 	int end;
// 	char *arg;
// 	int	processed_chevron;

// 	t_token *new;
// 	start = i;
// 	end = i;
// 	processed_chevron = 0;
	// printf("taille de start %d\n", start);
	// printf("taille de end avant: %d\n", end);
	// while(input[end] && input[end] != ' ' && input[end] != '\t' && input[end] != '|')
	// {
		// if (input[end] = '<' && input[end + 1] == '<')
		// 	here_doc;
		// if (input[end] == '<')
		// {
		// 	if (!processed_chevron)
		// 	{
		// 		processed_chevron = 1;
		// 		if (input[end + 1] == '<')
		// 		{
		// 			arg = ft_strndup(input + start, end - start + 2);
		// 			printf("arg: %s\n", arg);
		// 			new = init_node(arg, HERE_DOC);
		// 			add_back(token, new);
		// 			free(arg);
		// 		}
		// 		else
		// 		{
		// 			arg = ft_strndup(input + start, end - start + 1);
		// 			printf("arg: %s\n", arg);
		// 			new = init_node(arg, INPUT);
		// 			add_back(token, new);
		// 			free(arg);
		// 		}
		// 	}

		// }
		// else if (input[end] == '>')
		// {
		// 	if (!processed_chevron)
		// 	{
		// 		processed_chevron = 1;
		// 		if (input[end + 1] == '>')
		// 		{
		// 			arg = ft_strndup(input + start, end - start + 2);
		// 			printf("arg: %s\n", arg);
		// 			new = init_node(arg, APPEND);
		// 			add_back(token, new);
		// 			free(arg);
		// 		}
		// 		else
		// 		{
		// 			arg = ft_strndup(input + start, end - start + 1);
		// 			printf("arg: %s\n", arg);
		// 			new = init_node(arg, OUTPUT);
		// 			add_back(token, new);
		// 			free(arg);
		// 		}
		// 	}
		// }
		// else
		// {
		// 	printf("input[end] : %c:\n", input[end]);
		// 	arg = ft_strndup(input + start, end - start);
		// 	printf("arg: %s\n", arg);
		// 	new = init_node(arg, ARG);
		// 	add_back(token, new);
		// 	free(arg);
		// }


		// else if (input[end] = '>' && input[end + 1] == '>')
		// 	append
		// else if (input[end] = '>')
		// 	outfile
		// if (input[end] != 0)
	// 	end++;
	// }
	// free(arg);
	// return(end);
	// printf("input[end - 1]: %c\n", input[end - 1]);
	// if (input[end - 1] == '<')
	// {
	// 	arg = ft_strndup(input + start, end - start);
	// 	printf("arg: %s\n", arg);
	// 	new = init_node(arg, INPUT);
	// 	add_back(token, new);
	// }
	// else
	// {
	// 	arg = ft_strndup(input + start, end - start);
	// 	printf("arg: %s\n", arg);
	// 	new = init_node(arg, ARG);
	// 	add_back(token, new);
	// }
	// free(arg);
	// return (end);
// }

// t_token	*clean_arg(t_token **token, Token_type type)
// {
// 	t_token	*temp;

// 	temp = *token;
// 	while (temp != NULL)
// 	{
// 		if(temp->type == type)
// 		{
// 			temp->content = ft_clean_space(temp->content);
// 		}
// 		temp = temp->next;
// 	}
// 	return(temp);
// }

// char	*ft_clean_space(char *content)
// {
// 	int		i;
// 	int		flag;
// 	char	*temp;

// 	i = 0;
// 	flag = 0;
// 	temp = (char *)malloc(sizeof(char) * (ft_strlen(content) + 1));
// 	while(content[i] == ' ' || content[i] == '\t')
// 		i++;
// 	while (content[i])
// 	{
// 		if (content[i] == ' ' || content[i] == '\t')
// 			flag = 1;
// 		if (!(content[i] == ' ' || content[i] == '\t'))
// 		{
// 			if (flag == 1)
// 				temp[i] = ' ';
// 			flag = 0;
// 			temp[i] = content[i];
// 		}
// 		i++;
// 	}
// 	temp[i] = 0;
// 	return (temp);
// }

// int	tokenize_double_quote(t_token **token, char *input, int i, char **env)
// {
// 	int		start;
// 	int		end;
// 	int		count_quote;
// 	(void)	env;
// 	char	*arg;
// 	t_token	*new;

// 	start = i;
// 	end = i;
// 	count_quote = 0;
// 	while(input[end])
// 	{
// 		if (input[end] == '"')
// 			count_quote++;
// 		end++;
// 	}
// 	if (count_quote % 2 != 0)
// 	{
// 		perror("pas de seconde double quote\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	printf("end: %d \n", end);
// 	arg = ft_strndup(input + start, end - start);
// 	new = init_node(arg, ARG);
// 	add_back(token, new);
// 	free(arg);
// 	return (end + 1);
// }

// int	tokenize_simple_quote(t_token **token, char *input, int i)
// {
// 	int		start;
// 	int		end;
// 	int		count_quote;
// 	char	*arg;
// 	t_token	*new;

// 	start = i;
// 	end = i;
// 	count_quote = 0;
// 	while(input[end])
// 	{
// 		if (input[end] == '\'')
// 			count_quote++;
// 		end++;
// 	}
// 	if (count_quote % 2 != 0)
// 	{
// 		perror("pas de seconde simple quote\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	arg = ft_strndup(input + start, end - start);
// 	new = init_node(arg, ARG);
// 	add_back(token, new);
// 	free(arg);
// 	return (end + 1);
// }

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
