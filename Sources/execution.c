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

#include "../minishell.h"

/*
Check if there is just one cmd to
not execute pipe. Just send it to execution.

+ Check if we don't need a binary syntaxic tree.
*/

// Need input/here_doc before cmd.
// CHECK IF MULTIPLE REDIRECTIONS !

int	manage_input_redirection(t_token **current, char *node_content, int first_file)
{
	first_file = open(node_content, O_RDONLY, 0644);
	if (first_file == -1)
	{
		perror("Can't open first file\n");
		exit(EXIT_FAILURE);
	}
	dup2(first_file, STDIN_FILENO);
	close(first_file);
	*current = (*current)->next;
	return (first_file);
}

int	manage_output_redirection(char *node_content, int last_file)
{
	last_file = open(node_content, O_WRONLY | O_CREAT
		| O_TRUNC, 0644);
	if (last_file == -1)
	{
		perror("Can't open last file\n");
		exit(EXIT_FAILURE);
	}
	dup2(last_file, STDOUT_FILENO);
	close(last_file);
	return (last_file);
}

int	manage_append_redirection(char *node_content, int last_file)
{
	last_file = open(node_content, O_WRONLY | O_CREAT
		| O_APPEND, 0644);
	if (last_file == -1)
	{
		perror("Can't open last file\n");
		exit(EXIT_FAILURE);
	}
	dup2(last_file, STDOUT_FILENO);
	close(last_file);
	return (last_file);
}

void	exec_cmd_with_pipe(t_token **current, t_minishell *exit_code, int last_file, char **env)
{
	if (is_built_in((*current)->content) == 0)
		redir_builtin((*current)->content, exit_code, env, last_file);
	else
		create_pipes((*current)->content, env, exit_code, last_file);
	*current = (*current)->next;
	if ((*current)->next->type == PIPE)
		*current = (*current)->next;
	// dup2(saved_stdin, STDIN_FILENO);
	// dup2(saved_stdout, STDOUT_FILENO);
}

void	exec_simple_cmd(t_token **current, t_minishell *exit_code, char **env)
{
	if (builtin_or_not_builtin((*current)->content, env) == 0)
		;
	else
		exec_cmd_with_fork((*current)->content, env, exit_code);
}

void	manage_here_doc(t_token **current, t_minishell *exit_code, char *content)
{
	handle_here_doc(content, exit_code);
	*current = (*current)->next;
}

int	manage_redirection_input(t_token **current, t_minishell *exit_code, int first_file)
{
	if ((*current)->type == INPUT && ((*current)->next
			&& (*current)->next->type == CMD))
		first_file = manage_input_redirection(current, (*current)->content, first_file);
	else if ((*current)->type == HERE_DOC && ((*current)->next 
			&& (*current)->next->type == CMD))
		manage_here_doc(current, exit_code, (*current)->content); // To check !
	return (first_file);
}

int	manage_redirection_output(t_token **current, int last_file)
{
	if (((*current)->type == CMD && (((*current)->next
				&& (*current)->next->type == OUTPUT)
			|| ((*current)->next && (*current)->next->next
				&& (*current)->next->next->type == OUTPUT))))
		{
			if ((*current)->next->type == PIPE)
				last_file = manage_output_redirection((*current)->next->next->content, last_file);
			else
				last_file = manage_output_redirection((*current)->next->content, last_file);
		}
	else if (((*current)->type == CMD && (((*current)->next
				&& (*current)->next->type == APPEND)
			|| ((*current)->next && (*current)->next->next
				&& (*current)->next->next->type == APPEND))))
		last_file = manage_append_redirection((*current)->next->content, last_file);
	return (last_file);
}

int	manage_cmd_pipe(t_token **current, t_minishell *exit_code, int last_file, char **env)
{
	if (((*current)->type == CMD && (((*current)->next
				&& (*current)->next->type == PIPE)
			|| ((*current)->next && (*current)->next->next
				&& (*current)->next->next->type == PIPE))))
	{
		exec_cmd_with_pipe(current, exit_code, last_file, env);
		return (0);
	}
	return (1);
}

void	check_line(t_token **lst, char **env, t_minishell *exit_code)
{
	int		first_file;
	int		last_file;
	int		saved_stdin;
	int		saved_stdout;
	t_token	*current;

	current = *lst;
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	while (current)
	{
		first_file = 0;
		last_file = 0;
		first_file = manage_redirection_input(&current, exit_code, first_file);
		last_file = manage_redirection_output(&current, last_file);
		// if ((current->type == CMD && ((current->next
		// 				&& current->next->type == PIPE)
		// 			|| (current->next && current->next->next
		// 				&& current->next->next->type == PIPE))))
		// 	exec_cmd_with_pipe(&current, exit_code, last_file, env);
		if (manage_cmd_pipe(&current, exit_code, last_file, env) == 0)
			;
		else if (current->type == CMD)
		{
			exec_simple_cmd(&current, exit_code, env);
			dup2(saved_stdin, STDIN_FILENO);
			dup2(saved_stdout, STDOUT_FILENO);
		}
		current = current->next;
		dup2(saved_stdout, STDOUT_FILENO);
	}
}

// Alternative to the else !
// else if ((current->type == CMD && (current->next 
		//		&& current->next->type != PIPE)) // Ne marchera pas.
		// 	|| (current->next->next && (current->type == CMD 
		// 		&& current->next == NULL))) // Check si rien après où si redir.
		// {
		// 	printf("content : %s\n", current->content);
		// 	exec_cmd(current->content, env);
		// }

// while (node->next->next) // Check how to do the condition.
		// {
		// 	if (node->content == 'CMD')
		// 		create_pipes(node->content, env);
		// 	node = node->next;
		// }

void	redir_builtin(char *cmd, t_minishell *exit_code, char **env, int out)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		if (out == 0)
		{
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}
		builtin_or_not_builtin(cmd, env);
		exit(EXIT_SUCCESS);
	}
	else
		parent_builtin(fd, exit_code);
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

/*
Plusieurs input à la suite puis pipe : 
1. On lit chaque fichier qu'on écrit un par un
dans le même pipe.
2. On crée comme un fichier 4.
3. Ensuite on envoie dans execve ce "fichier" pour 
que la cmd l'utilise et ensuite envoie le résultat dans le pipe
vers le processus parent et que la prochaine cmd l'utilise.
*/

/*
MANAGE REDIRECTIONS :

// if (current->type == INPUT && (current->next
		// 		&& current->next->type == CMD))
		// 	first_file = manage_input_redirection(&current, current->content, first_file);
		// else if (current->type == HERE_DOC && (current->next->type == CMD))
		// 	manage_here_doc(&current, exit_code, current->content);
		// if ((current->type == CMD && ((current->next
		// 				&& current->next->type == OUTPUT)
		// 			|| (current->next && current->next->next
		// 				&& current->next->next->type == OUTPUT))))
		// 	last_file = manage_output_redirection(current->next->content, last_file);
		// else if ((current->type == CMD && ((current->next
		// 				&& current->next->type == APPEND)
		// 			|| (current->next && current->next->next
		// 				&& current->next->next->type == APPEND))))
		// 	last_file = manage_append_redirection(current->next->content, last_file);
*/
