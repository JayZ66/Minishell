/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <romlambe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:14:33 by jeguerin          #+#    #+#             */
/*   Updated: 2024/06/11 17:35:37 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*read_input(t_minishell *minishell)
{
	char	*input;

	input = readline("Tarpin_de_Minishell>");
	if (input == NULL)
	{
		free(input);
		if (minishell->token)
			free_lst_not_content(&minishell->token);
		if (minishell->clean_token)
			free_lst_not_content_clean(&minishell->clean_token);
		if (minishell->final_token)
			free_that_final_lst(&minishell->final_token);
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

void	initialize_minishell(t_minishell **minishell,
		t_minishell *exit_code, char **env)
{
	(*minishell) = (t_minishell *)ft_malloc(sizeof(t_minishell));
	(*minishell)->last_exit_status = 0;
	exit_code->last_exit_status = 0;
	(*minishell)->env = realloc_env(env);
	if ((*minishell)->env == NULL)
	{
		perror("Realloc env. failed\n");
		exit(1);
	}
	(*minishell)->token = NULL;
	(*minishell)->final_token = NULL;
	(*minishell)->clean_token = NULL;
}

int	(validate_args(int argc, char **argv))
{
	if (argc != 1 || argv[1])
		return (perror("Wrong nb of args\n"), 1);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	*minishell;
	char		*input;
	t_minishell	exit_code;

	if (validate_args(argc, argv))
		return (1);
	initialize_minishell(&minishell, &exit_code, env);
	manage_signals(minishell);
	while (1)
	{
		if (!read_and_extract(&input, minishell))
			continue ;
		if (handle_chevrons_and_spaces(minishell, input))
			continue ;
		minishell->clean_token = copy_lst(minishell->token);
		free_lst_not_content(&minishell->token);
		if (handle_redirections_main(minishell, input))
			continue ;
		minishell->final_token = final_clean_node(minishell->clean_token);
		free_lst_not_content_clean(&minishell->clean_token);
		execute_and_cleanup(minishell, &exit_code);
		free(input);
	}
	free_resources(minishell);
	return (0);
}	
