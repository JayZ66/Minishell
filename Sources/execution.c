/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:00:50 by marvin            #+#    #+#             */
/*   Updated: 2024/04/08 12:00:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Check if there is just one cmd to
not execute pipe. Just send it to execution.

+ Check if we don't need a binary syntaxic tree.
*/

// Need input/here_doc before cmd.
// CHECK IF MULTIPLE REDIRECTIONS !

void	exec_cmd_with_pipe(t_final_token **current, t_minishell *exit_code,
	int last_file, t_minishell *minishell)
{
	if (is_built_in((*current)->content) == 0)
		redir_builtin((*current)->content, exit_code, minishell, last_file);
	else
		create_pipes((*current)->content, minishell, exit_code, last_file);
	*current = (*current)->next;
	if ((*current)->next->type == PIPE)
		*current = (*current)->next;
}

void	exec_simple_cmd(t_final_token **current, t_minishell *minishell)
{
	if (builtin_or_not_builtin((*current)->content, minishell) == 0)
		;
	else
		exec_cmd_with_fork((*current)->content, minishell);
}

int	manage_redirection_output(t_final_token **current, int last_file,
	t_minishell *minishell)
{
	if ((*current)->type == CMD && ((*current)->next
			&& (*current)->next->type == OUTPUT))
		last_file = manage_output_redirection((*current)->next->content,
				last_file, minishell);
	else if ((*current)->type == CMD && (((*current)->next
				&& (*current)->next->next
				&& (*current)->next->next->type == OUTPUT)))
		last_file = manage_output_redirection((*current)->next->next->content,
				last_file, minishell);
	else if ((*current)->type == CMD && ((*current)->next
			&& (*current)->next->type == APPEND))
		last_file = manage_append_redirection((*current)->next->content,
				last_file, minishell);
	else if ((*current)->type == CMD && ((*current)->next
			&& (*current)->next->next
			&& (*current)->next->next->type == APPEND))
		last_file = manage_append_redirection((*current)->next->content,
				last_file, minishell);
	else if ((*current)->type == OUTPUT)
		last_file = manage_solo_output_redirection((*current)->content,
				last_file, minishell);
	else if ((*current)->type == APPEND)
		last_file = manage_solo_append_redirection((*current)->content,
				last_file, minishell);
	return (last_file);
}

int	manage_cmd_pipe(t_final_token **current, t_minishell *exit_code,
	int last_file, t_minishell *minishell)
{
	if (((*current)->type == CMD && (((*current)->next
					&& (*current)->next->type == PIPE)
				|| ((*current)->next && (*current)->next->next
					&& (*current)->next->next->type == PIPE))))
	{
		exec_cmd_with_pipe(current, exit_code, last_file, minishell);
		return (0);
	}
	return (1);
}
