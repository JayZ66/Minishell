/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:14:33 by jeguerin          #+#    #+#             */
/*   Updated: 2024/06/07 18:30:08 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_lst_not_content(t_token **token)
{
	t_token	*tmp;

	if (!(*token))
	{
		perror("Lst is empty, can't free\n");
		exit(EXIT_FAILURE);
	}
	while (*token)
	{
		tmp = (*token)->next;
		ft_free(*token);
		*token = tmp;
	}
	*token = NULL;
}

void	free_lst_not_content_clean(t_clean_token **token)
{
	t_clean_token	*tmp;

	if (!(*token))
	{
		perror("Lst is empty, can't free\n");
		exit(EXIT_FAILURE);
	}
	while (*token)
	{
		tmp = (*token)->next;
		ft_free(*token);
		*token = tmp;
	}
	*token = NULL;
}

char	*read_input(t_minishell *minishell, t_token *lst,
			t_clean_token *lst_clean, t_final_token *lst_final)
{
	char	*input;

	input = readline("Tarpin_de_Minishell>");
	if (input == NULL)
	{
		free(input);
		if (lst)
			free_lst_not_content(&lst);
		if (lst_clean)
			free_lst_not_content_clean(&lst_clean);
		if (lst_final)
			free_that_final_lst(&lst_final);
		printf("exit\n");
		minishell->last_exit_status = EXIT_FAILURE;
		free_tab(minishell->env);
		ft_free(minishell);
		ft_free_all();
		exit(EXIT_FAILURE);
	}
	if (ft_strncmp(input, ":", 1) == 0 || ft_strncmp(input, "!", 1) == 0)
		return (input = ft_strdup(""), input);
	add_history(input);
	return (input);
}

int	main(int argc, char **argv, char **env)
{
	char			*input;
	t_minishell		exit_code;
	t_token			*token;
	t_token			*head;
	t_clean_token	*clean_token;
	t_final_token	*final_token;
	t_minishell		*minishell;

	token = NULL;
	final_token = NULL;
	clean_token = NULL;
	(void)env;
	minishell = (t_minishell *)ft_malloc(sizeof(t_minishell));
	manage_signals(minishell);
	minishell->last_exit_status = 0;
	if (argc != 1 || argv[1])
		return (perror("Wrong nb of args\n"), 1);
	minishell->env = realloc_env(env);
	if (minishell->env == NULL)
		return (perror("Realloc env. failed\n"), 1);
	while (1)
	{
		input = read_input(minishell, token, clean_token, final_token);
		if (ft_strlen(input) == 0 || ft_isspace(input) == 1)
		{
			// rl_on_new_line();
			free(input);
			continue ;
		}
		token = extract_cmd(&token, input);
		head = token;
		// if (clean_chevron(token) == 1) // Pb bce always send 0 so if < alone => SEGFAULT !!!
		// {
		// 	printf("bash: %s error\n", input);
		// 	rl_on_new_line();
		// 	free(input);
		// 	free_that_lst(&token);
		// 	continue ;
		// }
		clean_spaces1(token);
		manage_node(token);
		clean_spaces2(token);
		if (verif_pipe(token) == 1)
		{
			rl_on_new_line();
			free(input);
			while (token)
			{
				ft_free(token->content);
				token = token->next;
			}
			continue ;
		}
		token = head;
		clean_token = copy_lst(token);
		free_lst_not_content(&token);
		test_redirection_input(clean_token);
		final_token = final_clean_node(clean_token);
		free_lst_not_content_clean(&clean_token);
		get_var_of_env(final_token, minishell);
		remove_quote(final_token);
		// print_lst(final_token);
		execute_commands_with_pipes_and_redirections(&final_token,
			minishell, &exit_code);
		free_that_final_lst(&final_token);
		free(input);
	}
	free_tab(minishell->env);
	ft_free(minishell);
	ft_free_all();
	return (0);
}
