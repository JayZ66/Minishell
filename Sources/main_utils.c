/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <romlambe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:48:31 by romlambe          #+#    #+#             */
/*   Updated: 2024/06/11 17:37:24 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	read_and_extract(char **input, t_minishell *minishell)
{
	*input = read_input(minishell);
	if (ft_strlen(*input) == 0 || ft_isspace(*input) == 1)
	{
		free(*input);
		return (0);
	}
	minishell->token = extract_cmd(&minishell->token, *input);
	return (1);
}

int	handle_chevrons_and_spaces(t_minishell *minishell, char *input)
{
	if (clean_chevron(minishell->token))
	{
		printf("bash: %s error\n", input);
		free(input);
		free_lst_not_content(&minishell->token);
		return (1);
	}
	clean_spaces1(minishell->token);
	manage_node(minishell->token);
	if (clean_spaces2(minishell->token) || verif_pipe(minishell->token))
	{
		free(input);
		while (minishell->token)
		{
			ft_free(minishell->token->content);
			minishell->token = minishell->token->next;
		}
		return (1);
	}
	return (0);
}

int	handle_redirections_main(t_minishell *minishell, char *input)
{
	if (test_redirection_input(minishell->clean_token))
	{
		free(input);
		free_lst_not_content_clean(&minishell->clean_token);
		return (1);
	}
	return (0);
}

void	execute_and_cleanup(t_minishell *minishell, t_minishell *exit_code)
{
	get_var_of_env(minishell->final_token, minishell);
	remove_quote(minishell->final_token);
	execute_commands_with_pipes_and_redirections(&minishell->final_token,
		minishell, exit_code);
	free_that_final_lst(&minishell->final_token);
}

void	free_resources(t_minishell *minishell)
{
	free_tab(minishell->env);
	ft_free(minishell);
	ft_free_all();
}
