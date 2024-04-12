/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:41:53 by marvin            #+#    #+#             */
/*   Updated: 2024/04/09 16:41:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	main(int argc, char **argv, char **env)
// {
// 	// char	*input;
// 	t_token	*token;
// 	(void)argc;
// 	(void)argv;

// 	token = NULL;
// 	(void)argc;
// 	(void)argv;
// 	// if (argc != 1 || argv[1])
// 	// 	return (perror("Wrong nb of args\n"), 1);
// 	env = realloc_env(env);
// 	if (env == NULL)
// 		return (perror("Realloc env. failed\n"), 1);
// 	// while (1)
// 	// {
// 		// input = read_input();
// 		// if (ft_strcmp(input, "exit") == 0)
// 		// {
// 		// 	free(input);
// 		// 	exit(0) ;
// 		// }
// 		token = create_command_list();
// 		if (!token)
// 			return(perror("Extract cmd failed\n"), 1);
// 		display_lst(token);
// 		check_line(&token, env);
// 		free_that_lst(&token);
// 	// }
// 	// free(input);
// 	free_tab(env);
// 	return (0);
// }

void append_exec_node(t_token **head, char *content, Token_type type) 
{
    t_token *new_node = (t_token *)malloc(sizeof(t_token));
    if (new_node == NULL) {
        perror("Allocation de mémoire échouée");
        exit(EXIT_FAILURE);
    }
    new_node->content = ft_strdup(content);
    new_node->type = type;
    new_node->next = NULL;

    if (*head == NULL)
        *head = new_node;
    else 
	{
        t_token *last = *head;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = new_node;
    }
}

t_token	*create_command_list()
{
	t_token	*head;

	head = NULL;
	// append_exec_node(&head, "file.txt", INPUT);
	append_exec_node(&head, "<< end", HERE_DOC);
	append_exec_node(&head, "cat", CMD);
	append_exec_node(&head, "", PIPE);
	// append_exec_node(&head, "cat", CMD);
	append_exec_node(&head, "", PIPE);
	// append_exec_node(&head, "cat", CMD);
	append_exec_node(&head, "", PIPE);
	append_exec_node(&head, "wc -l", CMD);
	append_exec_node(&head, "", PIPE);
	append_exec_node(&head, "cat", CMD);
    // append_exec_node(&head, "", PIPE);
	// append_exec_node(&head, "cat", CMD);
    append_exec_node(&head, "output.txt", APPEND);
	// append_exec_node(&head, "gcc_version.txt", OUTPUT);

	return (head);
}

void print_exec_list(t_token *head) 
{
    t_token *current = head;
    while (current != NULL) 
	{
        printf("[%d] %s\n", current->type, current->content);
        current = current->next;
    }
}

void	display_lst(t_token *line)
{
	printf("Contenu de la liste chaînée :\n");
    print_exec_list(line);
}