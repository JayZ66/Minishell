/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:49:09 by jeguerin          #+#    #+#             */
/*   Updated: 2024/05/26 18:04:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redir_builtin(char *cmd, t_minishell *exit_code, t_minishell *minishell,
	int out)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
	{
		minishell->last_exit_status = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		minishell->last_exit_status = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		child_builtin(fd, out);
		builtin_or_not_builtin(cmd, minishell, exit_code);
		minishell->last_exit_status = EXIT_SUCCESS;
		exit(EXIT_SUCCESS);
	}
	else
		parent_builtin(fd, exit_code);
}

void	child_builtin(int *fd, int out)
{
	if (out == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
}

void	parent_builtin(int *fd, t_minishell *exit_code)
{
	int	exit_status;

	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	waitpid(-1, &exit_status, 0);
	if (WIFEXITED(exit_status))
		exit_code->last_exit_status = WEXITSTATUS(exit_status);
}

void	exec_cmd(char *cmd, t_minishell *minishell)
{
	char	**cmd_line;
	char	*final_path;

	cmd_line = ft_split(cmd, ' ');
	if (!cmd)
	{
		minishell->last_exit_status = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
	final_path = get_path(cmd_line[0], minishell);
	if (!final_path)
	{
		free_tab(cmd_line);
		minishell->last_exit_status = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
	if (execve(final_path, cmd_line, minishell->env) == -1)
	{
		free_tab(cmd_line);
		free(final_path);
		minishell->last_exit_status = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
}
