/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:03:44 by romlambe          #+#    #+#             */
/*   Updated: 2024/05/03 17:19:46 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// UTILS LIST //

t_token	*lst_last(t_token *token)
{
	if (token == NULL)
	{
		perror("Token node is empty\n");
		exit(EXIT_FAILURE);
	}
	while (token->next)
		token = token->next;
	return (token);
}

void	add_back(t_token **token, t_token *new)
{
	t_token	*last;

	if (!token)
	{
		perror("List is empty\n");
		EXIT_FAILURE;
	}
	if (!(*token)) // To check !
		*token = new;
	else
	{
		last = lst_last(*token);
		last->next = new;
	}
}

void	print_lst(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		printf("Chaque node content : %s\n", tmp->content);
		printf("Chaque node type content : %u\n", tmp->type);
		tmp = tmp->next;
	}
}

void    free_that_lst(t_token **token)
{
    t_token    *tmp;

    if (!(*token))
    {
        perror("Lst is empty, can't free\n");
        exit(EXIT_FAILURE);
    }
    while (*token)
    {
        tmp = (*token)->next;
        free((*token)->content);
        free(*token);
        *token = tmp;
    }
    *token = NULL;
}

// INIT NODES //

t_token    *init_node(char *content, Token_type type)
{
    t_token    *token;

    token = (t_token *)malloc(sizeof(t_token));
    if (token == NULL)
    {
        perror("List has not been created\n");
        exit(EXIT_FAILURE);
    }
    token->content = ft_strdup(content); // Add token function here !
    if (token->content == NULL)
    {
        perror("Memory allocation failde\n");
        exit(EXIT_FAILURE);
    }
    token->type = type;
    token->next = NULL;
    return (token);
}

t_token    *init_node_separator(Token_type type)
{
    t_token    *token;

    token = (t_token *)malloc(sizeof(t_token));
    if (token == NULL)
    {
        perror("List has not been created\n");
        exit(EXIT_FAILURE);
    }
    token->content = NULL;
    token->type = type;
    token->next = NULL;
    return (token);
}


// INIT CLEAN NODE //

t_clean_token    *init_clean_node(char *content, Token_type type)
{
    t_clean_token    *token;

    token = (t_clean_token *)malloc(sizeof(t_clean_token));
    if (token == NULL)
    {
        perror("List has not been created\n");
        exit(EXIT_FAILURE);
    }
    token->content = ft_strdup(content); // Add token function here !
    if (token->content == NULL)
    {
        perror("Memory allocation failde\n");
        exit(EXIT_FAILURE);
    }
	token->type = type;
    token->next = NULL;
    return (token);
}

t_clean_token	*lst_clean_last(t_clean_token *token)
{
	if (token == NULL)
	{
		perror("Token node is empty\n");
		exit(EXIT_FAILURE);
	}
	while (token->next)
		token = token->next;
	return (token);
}

void	add_clean_back(t_clean_token **token, t_clean_token *new)
{
	t_clean_token	*last;

	// if (!(token))
	// {
	// 	perror("List is empty\n");
	// 	EXIT_FAILURE;
	// }
	if (!(*token)) // To check !
		*token = new;
	else
	{
		last = lst_clean_last(*token);
		last->next = new;
	}
}

void	print_clean_lst(t_clean_token *token)
{
	t_clean_token	*tmp;

	tmp = token;
	while (tmp)
	{
		printf("Chaque node clean content : %s\n", tmp->content);
		printf("Chaque node clean type content : %u\n", tmp->type);
		tmp = tmp->next;
	}
}

void    free_that_clean_lst(t_clean_token **token)
{
	t_clean_token	*tmp;

	// if (!(*token))
	// {
	// 	perror("Clean lst is empty, can't free\n");
	// 	exit(EXIT_FAILURE);
	// }
	while(*token)
	{
		tmp = (*token)->next;
		free((*token)->content);
		free(*token);
		*token = tmp;
	}
	*token = NULL;
}

// TOKENIZER INPUT OUTPUT APPEND HEREDOC //

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

// TOKENIZER ARG PIPE //

int	tokenize_pipe(t_token **token, int i)
{
	t_token	*new;

	new = init_node_separator(PIPE);
	add_back(token, new);
	i++;
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


// EXTRACT CMD //

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





