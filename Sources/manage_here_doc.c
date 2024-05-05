/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:44:43 by marvin            #+#    #+#             */
/*   Updated: 2024/04/14 18:44:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_here_doc(char *cmd, t_minishell *exit_code)
{
	int	pfd[2];
	int	pid;

	if (pipe(pfd) == -1)
	{
		perror("Pb while creating pipe\n");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Can't create processes\n");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		// signal(SIGTTIN, SIG_IGN);
		child_here_doc(pfd, cmd);
	}
	else
		parent_here_doc(pfd, cmd, exit_code);
}

// JE DOIS RECEVOIR LE NODE AVEC DES ESPACES !
void	child_here_doc(int *pfd, char *cmd)
{
	char	**limiter;
	char	*line;
	size_t	i;

	i = 0;
	limiter = ft_split(cmd, ' ');
	close(pfd[0]);
	dup2(pfd[1], STDOUT_FILENO);
	close(pfd[1]);
	while (limiter[i + 1] != NULL)
		i++;
	while (1)
	{
		line = get_next_line(0);
		if (ft_strncmp_limiter(line, limiter[i], ft_strlen(limiter[i])) == 0)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd(line, 1);
		free(line);
	}
}

// WEXITSTATUS : To put in a structure.
void	parent_here_doc(int *pfd, char *cmd, t_minishell *exit_code)
{
	int	exit_status;

	(void)cmd;
	close(pfd[1]);
	dup2(pfd[0], STDIN_FILENO);
	close(pfd[0]);
	waitpid(-1, &exit_status, 0);
	if (WIFEXITED(exit_status))
		exit_code->last_exit_status = WEXITSTATUS(exit_status);
	// printf("exit_code->last_exit_status = %d\n", exit_code->last_exit_status);
}