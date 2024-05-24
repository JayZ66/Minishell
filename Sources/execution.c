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

void	exec_simple_cmd(t_final_token **current, t_minishell *exit_code,
	t_minishell *minishell)
{
	if (builtin_or_not_builtin((*current)->content, minishell, exit_code) == 0)
		;
	else
		exec_cmd_with_fork((*current)->content, minishell, exit_code);
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

void	check_line(t_final_token **lst, t_minishell *minishell,
	t_minishell *exit_code)
{
	int				first_file;
	int				last_file;
	int				saved_stdin;
	int				saved_stdout;
	t_final_token	*current;

	current = *lst;
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	while (current)
	{
		first_file = 0;
		last_file = 0;
		first_file = manage_redirection_input(&current, exit_code, first_file);
		last_file = manage_redirection_output(&current, last_file, minishell);
		if (manage_cmd_pipe(&current, exit_code, last_file, minishell) == 0)
			;
		else if (current->type == CMD)
		{
			exec_simple_cmd(&current, exit_code, minishell);
			dup2(saved_stdin, STDIN_FILENO);
			dup2(saved_stdout, STDOUT_FILENO);
		}
		current = current->next;
		dup2(saved_stdout, STDOUT_FILENO);
	}
}

// Alternative to the else !
// else if ((current->type == CMD && (current->next 
		//		&& current->next->type != PIPE)) // Ne marchera pas.
		// 	|| (current->next->next && (current->type == CMD 
		// 		&& current->next == NULL))) // Check si rien après où si redir.
		// {
		// 	printf("content : %s\n", current->content);
		// 	exec_cmd(current->content, env);
		// }

// while (node->next->next) // Check how to do the condition.
		// {
		// 	if (node->content == 'CMD')
		// 		create_pipes(node->content, env);
		// 	node = node->next;
		// }
