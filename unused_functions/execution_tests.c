/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tests.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:35:52 by marvin            #+#    #+#             */
/*   Updated: 2024/04/19 11:35:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell"

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



// void	check_line(t_token **lst, char **env, t_minishell *exit_code)
// {
// 	int		first_file;
// 	int		last_file;
// 	t_token	*current;

// 	current = *lst;
// 	first_file = 0;
// 	last_file = 0;
// 	while (current)
// 	{
// 		if (current->type == INPUT && (current->next
// 				&& current->next->type == CMD))
// 		{
// 			first_file = open(current->content, O_RDONLY, 0644);
// 			if (first_file == -1)
// 			{
// 				perror("Can't open first file\n");
// 				exit(EXIT_FAILURE);
// 			}
// 			dup2(first_file, STDIN_FILENO);
// 			close(first_file);
// 			current = current->next;
// 		}
// 		else if (current->type == HERE_DOC && (current->next->type == CMD))
// 		{
// 			handle_here_doc(current->content, exit_code);
// 			current = current->next;
// 		}
// 		if ((current->type == CMD && ((current->next
// 						&& current->next->type == OUTPUT)
// 					|| (current->next && current->next->next
// 						&& current->next->next->type == OUTPUT))))
// 		{
// 			last_file = open(current->next->content, O_WRONLY | O_CREAT
// 					| O_TRUNC, 0644);
// 			if (last_file == -1)
// 			{
// 				perror("Can't open last file\n");
// 				exit(EXIT_FAILURE);
// 			}
// 			dup2(last_file, STDOUT_FILENO);
// 			close(last_file);
// 		}
// 		else if ((current->type == CMD && ((current->next
// 						&& current->next->type == APPEND)
// 					|| (current->next && current->next->next
// 						&& current->next->next->type == APPEND))))
// 		{
// 			last_file = open(current->next->content, O_WRONLY | O_CREAT
// 					| O_APPEND, 0644);
// 			if (last_file == -1)
// 			{
// 				perror("Can't open last file\n");
// 				exit(EXIT_FAILURE);
// 			}
// 			dup2(last_file, STDOUT_FILENO);
// 			close(last_file);
// 		}
// 		if ((current->type == CMD && ((current->next
// 						&& current->next->type == PIPE)
// 					|| (current->next && current->next->next
// 						&& current->next->next->type == PIPE))))
// 		{
// 			create_pipes(current->content, env, exit_code);
// 			current = current->next;
// 			if (current->next->type == PIPE)
// 				current = current->next;
// 		}
// 		else if (current->type == CMD)
// 		{
// 			exec_cmd_with_fork(current->content, env, exit_code);
// 			dup2(STDIN_FILENO, 0);
//             dup2(STDOUT_FILENO, 1);
// 		}
// 		current = current->next;
// 		dup2(STDOUT_FILENO, 1);
// 	}
// 	// dup2(STDIN_FILENO, 0);
// 	// dup2(STDOUT_FILENO, 1);
// }


// void	exec_cmd_with_fork(char *cmd, char **env, t_minishell *exit_code)
// {
// 	char	**cmd_line;
// 	char	*final_path;
// 	int		pid;
// 	int		pfd[2];
// 	int		status;

// 	status = 0;
// 	// if (is_one_cmd(cmd) == 1)
// 	cmd_line = ft_split(cmd, ' ');
// 	if (!cmd)
// 		exit(EXIT_FAILURE);
// 	if (pipe(pfd) == -1)
// 	{
// 		exit(EXIT_FAILURE);
// 	}
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("Can't fork\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	else if (pid == 0)
// 	{
// 		dup2(pfd[1], STDOUT_FILENO);
// 		final_path = get_path(cmd_line[0], env);
// 		if (!final_path)
// 		{
// 			free_tab(cmd_line);
// 			exit(EXIT_FAILURE);
// 		}
// 		if (execve(final_path, cmd_line, env) == -1)
// 		{
// 			free_tab(cmd_line);
// 			free(final_path);
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	else
// 	{
// 		close(pfd[1]);
// 		dup2(pfd[0], STDIN_FILENO);
// 		close(pfd[0]);
// 		waitpid(pid, &status, 0); // Attend la fin du processus fils
//         if (WIFEXITED(status))
// 		{
//             exit_code->last_exit_status = WEXITSTATUS(status);
//             printf("Command executed with exit status: %d\n", exit_code->last_exit_status);
//             // Vous pouvez gérer le statut de sortie ici si nécessaire
// 		}
// 	}
// }
