/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:19:26 by marvin            #+#    #+#             */
/*   Updated: 2024/05/05 16:19:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fork_error(t_minishell *exit_code)
{
	perror("fork");
	exit_code->last_exit_status = EXIT_FAILURE;
	exit(EXIT_FAILURE);
}

void	moove_to_next_token(t_final_token **current)
{
	if ((*current)->next && ((*current)->next->type == OUTPUT
			|| (*current)->next->type == APPEND))
		*current = (*current)->next;
	*current = (*current)->next;
}

void	wait_processes(int *pid_array, int index)
{
	int	i;

	i = -1;
	while (++i < index)
		waitpid(pid_array[i], NULL, 0);
}

int	exec_loop(t_final_token **current, t_minishell *minishell,
	t_minishell *exit_code, int should_exit)
{
	int				pid_array[1024];
	int				index;
	int				file;
	pid_t			pid;

	index = 0;
	(void)should_exit;
	while (*current)
	{
		file = handle_redirections(current, minishell, exit_code);
		if (file == -1)
			break ;
		if (is_pipe_command(current))
		{
			pid = manage_fork(minishell, exit_code, current, file);
			pid_array[index++] = pid;
		}
		else if ((*current)->type == CMD)
			exec_simple_cmd(current, minishell);
		moove_to_next_token(current);
	}
	return (wait_processes(pid_array, index), 0);
}

void	execute_commands_with_pipes_and_redirections(t_final_token **lst,
	t_minishell *minishell, t_minishell *exit_code)
{
	t_final_token	*current;
	int				should_exit;
	int				saved_stdin;
	int				saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	should_exit = 0;
	current = *lst;
	should_exit = exec_loop(&current, minishell, exit_code, should_exit);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	if (should_exit)
		builtin_or_not_builtin("exit", minishell);
	close(saved_stdin);
	close(saved_stdout);
}
