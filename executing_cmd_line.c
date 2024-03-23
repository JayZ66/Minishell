/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_cmd_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:25:34 by marvin            #+#    #+#             */
/*   Updated: 2024/03/23 16:25:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Entrée attendue par pipex : 
- ./pipex_bonus file cat cat cat file2
- ./pipex_bonus file "cat" "cat" "cat -l" file2

TO CHECK : 
=> How to handle the files ? Bcse shell doesn't always need files.
=> How to handle redirections ??
*/


void	execute_pipe(int nb_args, char **cmd_line, char **env)
{
	int	cmd_args;
	int	last_file;
	int	first_file;
	
	if (nb_args < 4)
		return (perror("Wrong nb args\n"), 1);
	if (ft_strncmp(cmd_line[1], "here_doc", 8) == 0)
	{
		if (argc < 5)
			return (perror("Wrong nb args for here_doc\n"), 1);
		cmd_args = 2;
		// Open last file : See how to handle this.
		// Handle Here_doc
	}
	else
	{
		cmd_args = 1;
		// Open first file & redirection.
		// Open last file.
		// Close first file.
	}
	while (cmd_args < nb_args - 1) // To check nb. to avoid last cmd.
	{
		do_pipes(cmd_line[cmd_args], env); // To code.
		cmd_args++;
	}
	// Redirection last file.
	// Exec last cmd. outside of the loop.
	// Close last file.
}

void	do_pipes(char *cmd, char **env)
{
	int	pid;
	int	pfd[2];

	if (pipe(pfd) == -1)
	{
		perror("Creation of pipe failed\n");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Creation of processes failed\n");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close(pfd[0]);
		dup2(pfd[1], STDOUT_FILENO);
		close(pfd[1]);
		// Function to execute cmd.
	}
	else
	{
		close(pfd[1]);
		dup2(pfd[0], STDIN_FILENO);
		close(pfd[0]);
		wait(NULL);
	}
}