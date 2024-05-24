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

#include "../minishell.h"

// int	main(int argc, char **argv, char **env)
// {
// 	t_minishell	exit_code;
// 	char		*input;
// 	t_token		*token;
// 	// char	*result_env;
// 	(void)argc;
// 	(void)argv;
// 	token = NULL;
// 	if (argc != 1 || argv[1])
// 		return (perror("Wrong nb of args\n"), 1);
// 	exit_code.last_exit_status = 0;
// 	env = realloc_env(env);
// 	if (env == NULL)
// 		return (perror("Realloc env. failed\n"), 1);
// 	while (1)
// 	{
// 		input = read_input();
// 		if (ft_strcmp(input, "exit") == 0)
// 		{
// 			free(input);
// 			exit(0);
// 		}
// 		token = create_command_list();
// 		if (!token)
// 			return (perror("Extract cmd failed\n"), 1);
// 		display_lst(token);
// 		// check_line2(&token, env, &exit_code);
// 		execute_commands_with_pipes_and_redirections(&token, env, &exit_code);
// 		// execute_commands_with_pipes(&token);
// 		free_that_lst(&token);
// 		// token = create_command_list2();
// 		// if (!token)
// 		// 	return(perror("Extract cmd failed\n"), 1);
// 		// display_lst(token);
// 		// check_line(&token, env, &exit_code); // PB qd on exec. la 2ème ligne de cmd => C'est dans l'output de l'ancienne ligne !!!
// 		// free_that_lst(&token);
// 		// token = create_command_list3();
// 		// if (!token)
// 		// 	return(perror("Extract cmd failed\n"), 1);
// 		// display_lst(token);
// 		// check_line(&token, env, &exit_code);
// 		// free_that_lst(&token);
// 		// token = create_command_list4();
// 		// if (!token)
// 		// 	return(perror("Extract cmd failed\n"), 1);
// 		// display_lst(token);
// 		// check_line(&token, env, &exit_code);
// 		// free_that_lst(&token);
// 		// token = create_command_list5();
// 		// if (!token)
// 		// 	return(perror("Extract cmd failed\n"), 1);
// 		// display_lst(token);
// 		// check_line(&token, env, &exit_code);
// 		// free_that_lst(&token);
// 		// token = create_command_list6();
// 		// if (!token)
// 		// 	return(perror("Extract cmd failed\n"), 1);
// 		// display_lst(token);
// 		// check_line(&token, env, &exit_code);
// 		// free_that_lst(&token);
// 	}
// 	free(input);
// 	printf("Exit statut : %d\n", exit_code.last_exit_status);
// 	// printf("Variable d'environnement : %s\n", result_env);
// 	free_tab(env);
// 	return (0);
// }

void	append_exec_node(t_token **head, char *content, Token_type type)
{
	t_token	*new_node;
	t_token	*last;

	new_node = (t_token *)malloc(sizeof(t_token));
	if (new_node == NULL)
	{
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
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
}

t_token	*create_command_list(void)
{
	t_token	*head;

	head = NULL;
	// append_exec_node(&head, "$PATH", CMD);
	// append_exec_node(&head, "end.txt", INPUT);
	// append_exec_node(&head, "file.txt", INPUT);
	// append_exec_node(&head, "end.txt", INPUT);
	// append_exec_node(&head, "end.txt", INPUT);
	// append_exec_node(&head, "<< end", HERE_DOC);
	// append_exec_node(&head, "wc -l", CMD);
	// append_exec_node(&head, "OK.txt", APPEND);
	// append_exec_node(&head, "", PIPE);
	append_exec_node(&head, "file.txt", INPUT);
	append_exec_node(&head, "", PIPE);
	// append_exec_node(&head, "end.txt", INPUT);
	// append_exec_node(&head, "output.txt", INPUT);
	append_exec_node(&head, "cat", CMD);
	// append_exec_node(&head, "OK.txt", APPEND);
	// append_exec_node(&head, "", PIPE);
	// append_exec_node(&head, "end.txt", INPUT);
	// append_exec_node(&head, "cat", CMD);
	// append_exec_node(&head, "fin.txt", APPEND);
	// append_exec_node(&head, "", PIPE);
	// append_exec_node(&head, "ls", CMD);
	// append_exec_node(&head, "", PIPE);
	// append_exec_node(&head, "cat", CMD);
	// append_exec_node(&head, "", PIPE);
	// append_exec_node(&head, "echo -n \"COUCOU TOI\"", CMD);
	// append_exec_node(&head, "", PIPE);
	// append_exec_node(&head, "cat", CMD);
	// append_exec_node(&head, "", PIPE);
	// append_exec_node(&head, "cat -e", CMD);
	// append_exec_node(&head, "", PIPE);
	// append_exec_node(&head, "end.txt", INPUT);
	// append_exec_node(&head, "cat", CMD);
	// append_exec_node(&head, "", PIPE);
	// append_exec_node(&head, "cat", CMD);
	// append_exec_node(&head, "end.txt", APPEND);
	// append_exec_node(&head, "cat", CMD);
	// append_exec_node(&head, "file.txt", APPEND);
	// append_exec_node(&head, "../bonjour", OUTPUT);
	// append_exec_node(&head, "fin.txt", OUTPUT);
	return (head);
}

// t_token	*create_command_list2(void)
// {
// 	t_token	*head;

// 	head = NULL;
	// append_exec_node(&head, "srcs/bonjour", INPUT);
	// append_exec_node(&head, "<< end", HERE_DOC);
	// append_exec_node(&head, "echo hey", CMD);
	// append_exec_node(&head, "", PIPE);
	// append_exec_node(&head, "cat", CMD);
	// append_exec_node(&head, "", PIPE);
	// append_exec_node(&head, "cat", CMD);
	// append_exec_node(&head, "", PIPE);
	// append_exec_node(&head, "wc -l", CMD);
	// append_exec_node(&head, "", PIPE);
	// append_exec_node(&head, "cat", CMD);
	// append_exec_node(&head, "", PIPE);
	// append_exec_node(&head, "cat", CMD);
	// append_exec_node(&head, "../hello", OUTPUT);
	// append_exec_node(&head, "hello", APPEND);
	// append_exec_node(&head, "bonjour", APPEND);
	// append_exec_node(&head, "gcc_version.txt", OUTPUT);
// 	return (head);
// }

// t_token	*create_command_list3(void)
// {
// 	t_token	*head;

// 	head = NULL;
	// append_exec_node(&head, "prout", INPUT);
	// append_exec_node(&head, "<< end", HERE_DOC);
	// append_exec_node(&head, "cat bonjour", CMD);
	// append_exec_node(&head, "rm srcs/bonjour srcs/hello", CMD);
	// append_exec_node(&head, "", PIPE);
	// append_exec_node(&head, "cat", CMD);
	// append_exec_node(&head, "", PIPE);
	// append_exec_node(&head, "cat", CMD);
	// append_exec_node(&head, "", PIPE);
	// append_exec_node(&head, "wc -l", CMD);
	// append_exec_node(&head, "", PIPE);
	// append_exec_node(&head, "cat", CMD);
	// append_exec_node(&head, "", PIPE);
	// append_exec_node(&head, "cat", CMD);
	// append_exec_node(&head, "../bonjour", OUTPUT);
	// append_exec_node(&head, "../hello", OUTPUT);
	// append_exec_node(&head, "bonjour", OUTPUT);
	// append_exec_node(&head, "bonjour", APPEND);
	// append_exec_node(&head, "gcc_version.txt", OUTPUT);
// 	return (head);
// }

// t_token	*create_command_list4(void)
// {
	// t_token	*head;

	// head = NULL;
	// append_exec_node(&head, "prout", INPUT);
	// append_exec_node(&head, "<< end", HERE_DOC);
	// append_exec_node(&head, "cat srcs/bonjour srcs/hello", CMD);
	// append_exec_node(&head, "", PIPE);
	// append_exec_node(&head, "cat ../bonjour ../hello", CMD);
	// append_exec_node(&head, "", PIPE);
	// append_exec_node(&head, "cat", CMD);
	// append_exec_node(&head, "", PIPE);
	// append_exec_node(&head, "wc -l", CMD);
	// append_exec_node(&head, "", PIPE);
	// append_exec_node(&head, "cat", CMD);
	// append_exec_node(&head, "", PIPE);
	// append_exec_node(&head, "cat", CMD);
	// append_exec_node(&head, "bonjour", APPEND);
	// append_exec_node(&head, "hello", APPEND);
	// append_exec_node(&head, "srcs/bonjour", OUTPUT);
	// append_exec_node(&head, "srcs/hello", OUTPUT);
	// append_exec_node(&head, "gcc_version.txt", OUTPUT);
// 	return (head);
// }

// t_token	*create_command_list5(void)
// {
// 	t_token	*head;

// 	head = NULL;
// 	append_exec_node(&head, "hello", INPUT);
// 	append_exec_node(&head, "<< end", HERE_DOC);
// 	append_exec_node(&head, "ls srcs", CMD);
// 	append_exec_node(&head, "", PIPE);
// 	append_exec_node(&head, "cat", CMD);
// 	append_exec_node(&head, "", PIPE);
// 	append_exec_node(&head, "cat", CMD);
// 	append_exec_node(&head, "", PIPE);
// 	append_exec_node(&head, "wc -l", CMD);
// 	append_exec_node(&head, "", PIPE);
// 	append_exec_node(&head, "cat", CMD);
// 	append_exec_node(&head, "", PIPE);
// 	append_exec_node(&head, "cat", CMD);
// 	append_exec_node(&head, "bonjour", OUTPUT);
// 	append_exec_node(&head, "hello", OUTPUT);
// 	append_exec_node(&head, "bonjour", OUTPUT);
// 	append_exec_node(&head, "gcc_version.txt", OUTPUT);
// 	return (head);
// }

// t_token	*create_command_list6(void)
// {
// 	t_token	*head;

// 	head = NULL;
	// append_exec_node(&head, "hello", INPUT);
	// append_exec_node(&head, "<< end", HERE_DOC);
	// append_exec_node(&head, "cat srcs/bonjour", CMD);
	// append_exec_node(&head, "", PIPE);
	// append_exec_node(&head, "cat", CMD);
	// append_exec_node(&head, "", PIPE);
	// append_exec_node(&head, "cat", CMD);
	// append_exec_node(&head, "", PIPE);
	// append_exec_node(&head, "wc -l", CMD);
	// append_exec_node(&head, "", PIPE);
	// append_exec_node(&head, "cat", CMD);
	// append_exec_node(&head, "", PIPE);
	// append_exec_node(&head, "cat", CMD);
	// append_exec_node(&head, "bonjour", OUTPUT);
	// append_exec_node(&head, "hello", OUTPUT);
	// append_exec_node(&head, "bonjour", OUTPUT);
	// append_exec_node(&head, "gcc_version.txt", OUTPUT);
// 	return (head);
// }

void	print_exec_list(t_token *head)
{
	t_token	*current;

	current = head;
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
