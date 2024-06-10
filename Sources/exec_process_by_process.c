/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process_by_process.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:39:45 by marvin            #+#    #+#             */
/*   Updated: 2024/06/03 13:39:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	how_many_output(t_final_token **current)
{
	t_final_token	*tmp;
	char			*file;

	tmp = *current;
	while (tmp)
	{
		if (tmp->type == OUTPUT || tmp->type == APPEND)
		{
			file = tmp->content;
			while (tmp)
			{
				if (tmp->type == CMD && ft_strschr(tmp->content, file) == 0)
					return (1);
				else if (tmp->type == INPUT
					&& ft_strcmp(file, tmp->content) == 0)
					return (1);
				tmp = tmp->next;
			}
			break ;
		}
		tmp = tmp->next;
	}
	return (0);
}

void	type_of_cmd(t_final_token **current, t_minishell *minishell,
	t_minishell *exit_code, int last_file)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (manage_cmd_pipe(current, exit_code, last_file, minishell) == 0)
		;
	else if ((*current)->type == CMD)
	{
		exec_simple_cmd(current, minishell);
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
	}
}

int	manage_pipe_output(t_final_token **current, t_minishell *minishell,
	t_minishell *exit_code)
{
	int	first_file;
	int	last_file;
	int	saved_stdout;

	saved_stdout = dup(STDOUT_FILENO);
	if (how_many_output(current) == 1)
	{
		while (*current)
		{
			first_file = 0;
			last_file = 0;
			first_file = manage_redirection_input(current, exit_code,
					first_file);
			last_file = manage_redirection_output(current, last_file,
					minishell);
			type_of_cmd(current, minishell, exit_code, last_file);
			if ((*current)->next && (*current)->next->type == OUTPUT)
				*current = (*current)->next;
			*current = (*current)->next;
			dup2(saved_stdout, STDOUT_FILENO);
		}
		return (1);
	}
	else
		return (0);
}

int	handle_redirections(t_final_token **current, t_minishell *minishell,
	t_minishell *exit_code)
{
	int	first_file;
	int	last_file;

	first_file = 0;
	last_file = 0;
	if (manage_pipe_output(current, minishell, exit_code) == 1)
		return (-1);
	first_file = manage_redirection_input(current, exit_code, first_file);
	last_file = manage_redirection_output(current, last_file, minishell);
	if (first_file != 0 || last_file != 0)
		return (last_file);
	return (0);
}
