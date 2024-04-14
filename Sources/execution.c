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
// 			// last_file = open(node->content, O_WRONLY 
//					| O_CREAT| O_TRUNC, 0644);
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
// 			last_file = open(node->content, O_WRONLY | O_CREAT 
//					| O_APPEND, 0644);
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

// Need input/here_doc before cmd.

void	check_line(t_token **lst, char **env)
{
	int		first_file;
	int		last_file;
	t_token	*current;

	current = *lst;
	while (current)
	{
		if (current->type == INPUT && (current->next
				&& current->next->type == CMD))
		{
			first_file = open(current->content, O_RDONLY, 0644);
			if (first_file == -1)
			{
				perror("Can't open first file\n");
				exit(EXIT_FAILURE);
			}
			dup2(first_file, STDIN_FILENO);
			close(first_file);
			current = current->next;
		}
		else if (current->type == HERE_DOC && (current->next->type == CMD))
		{
			handle_here_doc(current->content);
			current = current->next;
		}
		if ((current->type == CMD && ((current->next
						&& current->next->type == OUTPUT)
					|| (current->next && current->next->next
						&& current->next->next->type == OUTPUT))))
		{
			last_file = open(current->next->content, O_WRONLY | O_CREAT
					| O_TRUNC, 0644);
			if (last_file == -1)
			{
				perror("Can't open last file\n");
				exit(EXIT_FAILURE);
			}
			dup2(last_file, STDOUT_FILENO);
			close(last_file);
		}
		else if ((current->type == CMD && ((current->next
						&& current->next->type == APPEND)
					|| (current->next && current->next->next
						&& current->next->next->type == APPEND))))
		{
			last_file = open(current->next->content, O_WRONLY | O_CREAT
					| O_APPEND, 0644);
			if (last_file == -1)
			{
				perror("Can't open last file\n");
				exit(EXIT_FAILURE);
			}
			dup2(last_file, STDOUT_FILENO);
			close(last_file);
		}
		if ((current->type == CMD && ((current->next
						&& current->next->type == PIPE)
					|| (current->next && current->next->next
						&& current->next->next->type == PIPE))))
		{
			create_pipes(current->content, env);
			current = current->next;
			if (current->next->type == PIPE)
				current = current->next;
		}
		else
		{
			exec_cmd(current->content, env);
		}
		current = current->next;
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
