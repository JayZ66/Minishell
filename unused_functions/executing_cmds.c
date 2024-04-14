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
- ./pipex_bonus here_doc "LIMITER" "cat" "cat" file2

TO CHECK : 
=> How to handle the files ? Bcse shell doesn't always need files.
=> How to handle redirections ??
*/

void	do_pipes(char *cmd, char **env)
{
	int	pid;
	int	pfd[2];

	(void)cmd;
	(void)env;
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
		exec_cmd(cmd, env); // Function to execute cmd.
	}
	else
	{
		close(pfd[1]);
		dup2(pfd[0], STDIN_FILENO);
		close(pfd[0]);
		wait(NULL);
	}
}

void	exec_cmd(char *cmd, char **env)
{
	char	*path;
	char	**args;

	args = ft_split(cmd, ' ');
	if (!args)
	{
		perror("Can't split my cmd\n");
		exit(EXIT_FAILURE);
	}
	path = select_path(args[0], env);
	if (!path)
	{
		perror("Can't get the right path\n");
		free_tab(args);
		exit(EXIT_FAILURE);
	}
	if (execve(path, args, env) == -1)
	{
		perror("Can't execute cmd\n");
		free_tab(args);
		free(path);
		exit(EXIT_FAILURE);
	}
}

void	execute_pipe(int nb_args, char **cmd_line, char **env)
{
	int	cmd_args;
	int	last_file;
	int	first_file;
	
	if (nb_args < 4)
		return (perror("Wrong nb args\n"));
	if (ft_strncmp(cmd_line[1], "here_doc", 8) == 0)
	{
		if (nb_args < 5)
			return (perror("Wrong nb args for here_doc\n"));
		cmd_args = 2;
		// Open last file : See how to handle this.
		// Handle Here_doc
	}
	else
	{
		cmd_args = 1;
		first_file = manage_file(nb_args, cmd_line, 0);
		dup2(first_file, STDIN_FILENO); // Open first file & redirection.
		close(first_file);
		last_file = manage_file(nb_args, cmd_line, 1); 	// Open last file.
	}
	while (cmd_args < nb_args - 2) // To check nb. to avoid last cmd.
	{
		do_pipes(cmd_line[cmd_args], env); // To code.
		cmd_args++;
	}
	dup2(last_file, STDOUT_FILENO); // Redirection last file.
	exec_cmd(cmd_line[nb_args - 2], env); // Exec last cmd. outside of the loop.
	close(last_file);
}