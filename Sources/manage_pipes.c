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

void	create_pipes(char *cmd, t_minishell *minishell,
	t_minishell *exit_code, int output)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
	{
		exit_code->last_exit_status = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		exit_code->last_exit_status = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		child_process(fd, cmd, minishell, output);
	}
	else
	{
		parent_process(fd, cmd, exit_code);
	}
}

void	child_process(int *pfd, char *cmd, t_minishell *minishell, int output)
{
	(void)cmd;
	if (output == 0)
	{
		close(pfd[0]);
		dup2(pfd[1], STDOUT_FILENO);
		close(pfd[1]);
	}
	exec_cmd(cmd, minishell);
}

void	parent_process(int *pfd, char *cmd, t_minishell *exit_code)
{
	int	exit_status;

	(void)cmd;
	(void)exit_code;
	exit_status = 0;
	close(pfd[1]);
	dup2(pfd[0], STDIN_FILENO);
	close(pfd[0]);
	waitpid(-1, &exit_status, 0);
	if (WIFEXITED(exit_status))
		exit_code->last_exit_status = WEXITSTATUS(exit_status);
}

// void parent_process(int *pfd, char *cmd, char **env, t_minishell *exit_code) 
//{
//     int exit_status;
//     (void)cmd;
//     (void)env;
//     (void)exit_code;
//     exit_status = 0;
//     close(pfd[1]);

//     // Vérifier si l'entrée standard est un terminal interactif
//     if (isatty(STDIN_FILENO)) {
//         // Configurer l'entrée standard en mode non bloquant
//         int flags = fcntl(STDIN_FILENO, F_GETFL);
//         fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
//     }

//     // Rediriger l'entrée standard vers le tuyau
//     dup2(pfd[0], STDIN_FILENO);
//     close(pfd[0]);

//     // Attendre le processus enfant
//     waitpid(-1, &exit_status, 0);
//     if (WIFEXITED(exit_status)) {
//         exit_code->last_exit_status = WEXITSTATUS(exit_status);
//     }
// }

// WIFEXITED : Maj de la variable qui stocke le code de
// sortie de la cmd avec le code de sortie de la cmd.
