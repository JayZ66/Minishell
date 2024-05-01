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

#include "../minishell.h"

void	create_pipes(char *cmd, char **env, t_minishell *exit_code, int output)
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
		child_process(fd, cmd, env, output);
	}
	else
		parent_process(fd, cmd, env, exit_code);
}

void	child_process(int *pfd, char *cmd, char **env, int output)
{
	(void)cmd;
	(void)env;
	if (output == 0)
	{
		close(pfd[0]);
		dup2(pfd[1], STDOUT_FILENO);
		close(pfd[1]);
	}
	exec_cmd(cmd, env);
}

void	parent_process(int *pfd, char *cmd, char **env, t_minishell *exit_code)
{
	int	exit_status;

	(void)cmd;
	(void)env;
	(void)exit_code;
	exit_status = 0;
	close(pfd[1]);
	dup2(pfd[0], STDIN_FILENO);
	close(pfd[0]);
	waitpid(-1, &exit_status, 0);
	if (WIFEXITED(exit_status))
		exit_code->last_exit_status = WEXITSTATUS(exit_status);
}

// WIFEXITED : Maj de la variable qui stocke le code de
// sortie de la cmd avec le code de sortie de la cmd.