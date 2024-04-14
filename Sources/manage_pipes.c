/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:43:27 by marvin            #+#    #+#             */
/*   Updated: 2024/04/14 18:43:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipes(char *cmd, char **env)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
	{
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		child_process(fd, cmd, env);
	}
	else
		parent_process(fd, cmd, env);
}

void	child_process(int *pfd, char *cmd, char **env)
{
	(void)cmd;
	(void)env;
	close(pfd[0]);
	dup2(pfd[1], STDOUT_FILENO);
	close(pfd[1]);
	exec_cmd(cmd, env);
}

void	parent_process(int *pfd, char *cmd, char **env)
{
	int	exit_status;

	(void)cmd;
	(void)env;
	exit_status = 0;
	close(pfd[1]);
	dup2(pfd[0], STDIN_FILENO);
	close(pfd[0]);
	wait(&exit_status);
	if (WIFEXITED(exit_status))
		exit_status = WEXITSTATUS(exit_status);
}
