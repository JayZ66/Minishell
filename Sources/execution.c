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
	first_file = 0;
	last_file = 0;
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
			handle_here_doc(current->content, exit_code);
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
			if (builtin_or_not_builtin(current->content, env) == 0)
			{
				// Si output on ne redirige pas.
				// Si pas d'output on redirige.
			}
			create_pipes(current->content, env, exit_code);
			current = current->next;
			if (current->next->type == PIPE)
				current = current->next;
		}
		else if (current->type == CMD)
		{
			if (builtin_or_not_builtin(current->content, env) == 0)
				;
			else
				exec_cmd_with_fork(current->content, env, exit_code);
			dup2(saved_stdin, STDIN_FILENO);
			dup2(saved_stdout, STDOUT_FILENO);
		}
		current = current->next;
	}
	// dup2(saved_stdin, STDIN_FILENO);
	// dup2(saved_stdout, STDOUT_FILENO);
} 

// CHECK SI PLS REDIRECTIONS ET SI APRES EXEC OU CHQ LIGNE DE CMD !!

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

/*
Plusieurs input à la suite puis pipe : 
1. On lit chaque fichier qu'on écrit un par un
dans le même pipe.
2. On crée comme un fichier 4.
3. Ensuite on envoie dans execve ce "fichier" pour 
que la cmd l'utilise et ensuite envoie le résultat dans le pipe
vers le processus parent et que la prochaine cmd l'utilise.
*/