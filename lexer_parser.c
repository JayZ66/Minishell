/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:03:44 by romlambe          #+#    #+#             */
/*   Updated: 2024/05/05 17:02:41 by romlambe         ###   ########.fr       */
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

// void    free_that_lst(t_token **token)
// {
//     t_token    *tmp;

//     if (!(*token))
//     {
//         perror("Lst is empty, can't free\n");
//         exit(EXIT_FAILURE);
//     }
//     while (*token)
//     {
//         tmp = (*token)->next;
//         free((*token)->content);
//         free(*token);
//         *token = tmp;
//     }
//     *token = NULL;
// }

int	string_is_space(char *token)
{
	if (token == NULL)
		return (1);
	while (token)
	{
		if (*token != ' ' && *token != '\t')
			return (0);
		token++;
	}
	return (1);
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

// CLEAN NODES //

void	clean_spaces(t_token *token)
{
	int	i;
	int	j;
	int prev_space;
	while (token != NULL)
	{
		if (token->content != NULL)
		{
			i = 0;
			j = 0;
			prev_space = 0;
			while (token->content[i] == ' ')
				i++;
			while (token->content[i] != '\0')
			{
				if (token->content[i] != ' ' || !prev_space)
				{
					token->content[j++] = token->content[i];
					prev_space = (token->content[i] == ' ');
				}
				i++;
			}
			token->content[j] = '\0';
		}
		token = token->next;
	}
}

void	clean_spaces2(t_token *token)
{
	int	i;

	// i = 0;
	while (token)
	{
		i = 0;
		if (token->type == INPUT || token->type == OUTPUT || token->type == APPEND
			|| token->type == HERE_DOC)
		{
			while (token->content[i] && token->content[i] != ' '
				&& token->content[i] != '\t')
				i++;
			token->content = ft_strndup(token->content, i);
		}
		printf("token->content clean space %s\n", token->content);
		token = token->next;
	}

}

void	clean_chevron(t_token *token)
{
	int	i;
	int	j;
	while (token != NULL)
	{
		if (token->type == INPUT || token->type == OUTPUT
			|| token->type == APPEND|| token->type == HERE_DOC)
		{
			if (token->content)
			{
				i = 0;
				j = 0;
				while (token->content[i])
				{
					if (token->content[i] == '<' || token->content[i] == '>'
						|| token->content[i] == '|')
						i++;
					else
						token->content[j++] = token->content[i++];
				}
				token->content[j] = '\0';
			}
		}
		token = token->next;
	}
}

void	cut_node(t_token *token)
{
	char	*temp;
	t_token	*new;
	int		i;

	i = 0;
	while (token->content[i] && token->content[i] != ' ')
		i++;
	temp = ft_strndup(token->content, i);
	if (string_is_space(token->content + i) == 0)
	{
		while (token->content[i] == ' ')
			i++;
		if (!token->content[i])
			return ;
		new = (t_token *)malloc(sizeof(t_token));
		if (new == NULL)
		{
			perror("Erreur d'allocation de mémoire");
			exit(EXIT_FAILURE);
		}
		new->content = ft_strdup(token->content + i);
		new->type = ARG;
		new->next = token->next;
		token->next = new;
		free(token->content);
		token->content = ft_strdup(temp);
		free(temp);
	}
}

void	manage_node(t_token *token)
{
	while(token)
	{
		if (token->type == INPUT)
			cut_node(token);
		if (token->type == OUTPUT)
			cut_node(token);
		if (token->type == APPEND)
			cut_node(token);
		if (token->type == HERE_DOC)
			cut_node(token);
		token = token->next;
	}
}

// REDIRECTION //

void	test_redirection_input(t_clean_token *clean_node)
{
	while (clean_node && clean_node->next)
	{
		if (clean_node->type == INPUT && clean_node->next->type == INPUT)
			redirection_input(clean_node);
		else if (clean_node->type == OUTPUT && clean_node->next->type == OUTPUT)
			redirection_output(clean_node);
		else if (clean_node->type == APPEND && clean_node->next->type == APPEND)
			redirection_append(clean_node);
		clean_node = clean_node->next;
	}
}

void	redirection_input(t_clean_token *clean_node)
{
	int	filein;

	filein = 0;
	filein = open(clean_node->content, O_RDONLY, 0644);

	if (filein == -1)
	{
		perror("Erreur file");
		exit(EXIT_FAILURE);
	}
	close(filein);
}

void	redirection_output(t_clean_token *clean_node)
{
	int	fileout;

	fileout = 0;
	fileout = open(clean_node->content, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fileout == -1)
	{
		perror("Erreur file de sortie");
		exit(EXIT_FAILURE);
	}
	close(fileout);
}

void	redirection_append(t_clean_token *clean_node)
{
	int	fileout;

	fileout = 0;
	fileout = open(clean_node->content, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (fileout == -1)
	{
		perror("Erreur file de sortie");
		exit(EXIT_FAILURE);
	}
	close(fileout);
}


int	input_in_bloc(t_clean_token *token, int i)
{
	while (token != NULL && token->type != PIPE)
	{
		if (token->type == INPUT)
			i++;
		token = token->next;
	}
	return (i);
}

// COPY LIST //

t_clean_token *copy_lst(t_token *token)
{
    // t_token *head = token;
    t_clean_token *clean_list = NULL;
    char *content = NULL;

    while (token != NULL)
    {
        t_token *block_start = token; // Pointeur de départ pour le bloc actuel

        while (token != NULL && token->type != PIPE)
        {
            if (token->type == INPUT || token->type == HERE_DOC)
            {
                content = ft_strdup(token->content);
                t_clean_token *new = init_clean_node(content, token->type);
                add_clean_back(&clean_list, new);
                free(content);
            }
            token = token->next;
        }

        // Ajouter les arguments pour ce bloc
        token = block_start;
        while (token != NULL && token->type != PIPE)
        {
            if (token->type == ARG)
            {
                content = ft_strdup(token->content);
                t_clean_token *new = init_clean_node(content, token->type);
                add_clean_back(&clean_list, new);
                free(content);
            }
            token = token->next;
        }

        // Ajouter les sorties pour ce bloc
        token = block_start;
        while (token != NULL && token->type != PIPE)
        {
            if (token->type == OUTPUT || token->type == APPEND)
            {
                content = ft_strdup(token->content);
                t_clean_token *new = init_clean_node(content, token->type);
                add_clean_back(&clean_list, new);
                free(content);
            }
            token = token->next;
        }

        // Passer au prochain bloc s'il y en a un
        if (token!= NULL)
        {
			if (token->type == PIPE)
			{
				content = ft_strdup("|");
                t_clean_token *new = init_clean_node(content, token->type);
                add_clean_back(&clean_list, new);
                free(content);
			}
            token = token->next; // Avancer pour sauter le pipe
        }
    }
    return clean_list;
}


char	*ft_strndup(const char *s, size_t n)
{
	char	*dest;
	size_t	i;

	if (s == NULL || n == 0)
		return (NULL);
	dest = (char *)malloc(sizeof(char) * (n + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s[i] && i < n)
	{
		dest[i] = s[i];
		if (dest[i] == '\n')
			dest[i] = '\0';
		i++;
	}
	dest[i] = '\0';
	printf("Ma string : %s\n", dest);
	return (dest);
}
