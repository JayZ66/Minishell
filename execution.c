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

#include "minishell.h"

/*
Check if there is just one cmd to
not execute pipe. Just send it to execution.

+ Check if we don't need a binary syntaxic tree.
*/

// void	check_line(t_exec *node, char **env)
// {
// 	int	first_file;
// 	int	last_file;
// 	int	cmd_args;
// 	t_exec	*last;

// 	last = lst_last(node);
// 	while (node->next) // CHECK SI LA BOUCLE EST HERE OR BELOW.
// 	{
// 		if (node->type == 'INPUT') // DO THE SAME FOR HERE_DOC.
// 		{
// 			first_file = open(node->content, O_RDONLY, 0644);
// 			// last_file = open(node->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 			if (first_file == -1 || last_file == -1)
// 			{
// 				perror("Can't open file\n");
// 				exit(EXIT_FAILURE);
// 			}
// 			dup2(first_file, STDIN_FILENO);
// 			close(first_file);
// 			cmd_args = 2;
// 		}
// 		else if (node->type == 'HERE_DOC')
// 		{
// 			last_file = open(node->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 			if (!last_file)
// 			{
// 				perror("Can't open file\n");
// 				exit(EXIT_FAILURE);
// 			}
// 			cmd_args = 3;
// 			handle_here_doc(node); // Check what we've to send.
// 		}
// 		else if (node->type == 'CMD' && node->next->type == 'PIPE')
// 		{
// 			execute_pipes(node->content, char **env);
// 		}
// 		else if (node->type == 'OUTPUT')
// 		else if (node->type == 'APPEND')
// 	}
// 	if (last->type == 'OUTPUT')
// 		dup2(last_file, STDOUT_FILENO);
// 	exec_cmd(node->content, env);
// 	close(last_file);
// }


void	check_line(t_token **lst, char **env)
{
	int	first_file;
	int	last_file;
	// int	cmd_args;
	// t_exec	*last;
	t_token	*current;

	// last = lst_last(node);
	current = *lst;
	while (current)
	{
		if (current->type == INPUT && (current->next && current->next->type == CMD)) // Check if cmd is necessary.
		{
			first_file = open(current->content, O_RDONLY, 0644);
			// last_file = open(node->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (first_file == -1)
			{
				perror("Can't open first file\n");
				exit(EXIT_FAILURE);
			}
			dup2(first_file, STDIN_FILENO);
			close(first_file);
			current = current->next;
		}
		else if (current->type == CMD && (current->next && current->next->type == HERE_DOC)) // CMD << LIMITER. ??
		{
			handle_here_doc(current->next->content); // How to exec. cmd.
		}
		if ((current->type == CMD && ((current->next && current->next->type == OUTPUT) 
			|| (current->next && current->next->next && current->next->next->type == OUTPUT)))) // Check if we need to check it at firt.
		{
			last_file = open(current->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (last_file == -1)
			{
				perror("Can't open last file\n");
				exit(EXIT_FAILURE);
			}
			dup2(last_file, STDOUT_FILENO);
			printf("HELLO YOU\n");
			close(last_file);
		}
		else if ((current->type == CMD && ((current->next && current->next->type == APPEND) 
			|| (current->next && current->next->next && current->next->next->type == APPEND))))
		{
			last_file = open(current->next->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (last_file == -1)
			{
				perror("Can't open last file\n");
				exit(EXIT_FAILURE);
			}
			dup2(last_file, STDOUT_FILENO);
			close(last_file);
		}
		if ((current->type == CMD && ((current->next && current->next->type == PIPE) 
			|| (current->next && current->next->next && current->next->next->type == PIPE))))
		{
			create_pipes(current->content, env);
			current = current->next;
			if (current->next->type == PIPE)
				current = current->next;
		}
		// else if ((current->type == CMD && (current->next && current->next->type != PIPE)) // Ne marchera pas.
		// 	|| (current->next->next && (current->type == CMD && current->next == NULL))) // Check comment faire si rien après où si redirection.
		// {
		// 	printf("content : %s\n", current->content);
		// 	exec_cmd(current->content, env);
		// }
		else
		{
			exec_cmd(current->content, env);
		}
		current = current->next;
	}
}

// while (node->next->next) // Check how to do the condition.
		// {
		// 	if (node->content == 'CMD')
		// 		create_pipes(node->content, env);
		// 	node = node->next;
		// }

void	handle_here_doc(char *cmd) // CMD << LIMITER
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
		child_here_doc(pfd, cmd);
	else
		parent_here_doc(pfd, cmd);
}

void	child_here_doc(int *pfd, char *cmd)
{
	char	**limiter;
	char	*line;
	size_t	i;

	i = 0;
	limiter = ft_split(cmd, ' '); // JE DOIS RECEVOIR LE NODE AVEC DES ESPACES !
	close(pfd[0]);
	dup2(pfd[1], STDOUT_FILENO);
	close(pfd[1]);
	while(limiter[i + 1] != NULL) // Check how to read here_doc !
		i++;
	while (1)
	{
		line = get_next_line(0); // Check if we need it.
		if (ft_strncmp_limiter(line, limiter[i], ft_strlen(limiter[i])) == 0)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd(line, 1);
		free(line);
	}
}

void	parent_here_doc(int *pfd, char *cmd)
{
	int	exit_status;

	exit_status = 0;
	(void)cmd;
	close(pfd[1]);
	dup2(pfd[0], STDIN_FILENO);
	close(pfd[0]);
	wait(&exit_status);
	if (WIFEXITED(exit_status)) // To put in a structure.
    	exit_status = WEXITSTATUS(exit_status); // Check if works.
}

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
	wait(&exit_status); // Need to use the waitpid() function to get $? code.
	if (WIFEXITED(exit_status)) // To put in a structure.
    	exit_status = WEXITSTATUS(exit_status);
}

void	exec_cmd(char *cmd, char **env)
{
	char	**cmd_line;
	char	*final_path;

	cmd_line = ft_split(cmd, ' ');
	if (!cmd)
		exit(EXIT_FAILURE);
	final_path = get_path(cmd_line[0], env);
	if (!final_path)
	{
		free_tab(cmd_line);
		exit(EXIT_FAILURE);
	}
	if (execve(final_path, cmd_line, env) == -1)
	{
		free_tab(cmd_line);
		free(final_path);
		exit(EXIT_FAILURE);
	}
}

char	*get_path(char *cmd, char **env)
{
	char	*tmp_path;
	char	*final_path;
	char	**path;
	size_t	i;

	path = select_path(env);
	i = 0;
	if (!path)
		exit(EXIT_FAILURE);
	while (path[i])
	{
		tmp_path = ft_strjoin(path[i], "/");
		final_path = ft_strjoin(tmp_path, cmd);
		free(tmp_path);
		if (access(final_path, X_OK) == 0)
		{
			return (free_tab(path), final_path);
		}
		free(final_path);
		i++;
	}
	free_tab(path);
	perror("The executable doesn't exist in the repo\n");
	return (NULL);
}

char	**select_path(char **env)
{
	size_t	i;
	size_t	j;
	char	**all_path;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j])
		{
			if (env[i][j] == '=')
			{
				if (ft_strncmp(env[i], "PATH", 4) == 0)
				{
					j++;
					all_path = ft_split(env[i] + j, ':');
					return (all_path);
				}
			}
			j++;
		}
		i++;
	}
	perror("Can't find the var. path in env.\n");
	return (NULL);
}