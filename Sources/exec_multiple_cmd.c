/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multiple_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:44:47 by marvin            #+#    #+#             */
/*   Updated: 2024/06/03 13:44:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_pipe(int *pipefd, t_minishell *minishell, t_minishell *exit_code,
	t_final_token **current)
{
	(void)pipefd;
	exec_simple_cmd(current, minishell);
	exit_code->last_exit_status = EXIT_SUCCESS;
	exit(EXIT_SUCCESS);
}

void	parent_pipe(int *pipefd)
{
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
}

pid_t	manage_fork(t_minishell *minishell, t_minishell *exit_code,
	t_final_token **current, int file)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		pipe_error(exit_code);
	pid = fork();
	if (pid == -1)
		fork_error(exit_code);
	else if (pid == 0)
	{
		if (file == 0)
		{
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
		}
		child_pipe(pipefd, minishell, exit_code, current);
	}
	else
		parent_pipe(pipefd);
	return (pid);
}

int	is_pipe_command(t_final_token **current)
{
	return (((*current)->type == CMD
			&& (((*current)->next && (*current)->next->type == PIPE)
				|| ((*current)->next && (*current)->next->next
					&& (*current)->next->next->type == PIPE))));
}

void	pipe_error(t_minishell *exit_code)
{
	perror("pipe");
	exit_code->last_exit_status = EXIT_FAILURE;
	exit(EXIT_FAILURE);
}
