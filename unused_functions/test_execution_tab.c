/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_execution_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:32:45 by marvin            #+#    #+#             */
/*   Updated: 2024/04/09 16:32:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_line(char **cmd_line, char **env)
{
	int	file_in;
	int	file_out;
	int	cmd_args;

	while (node->next) // CHECK SI LA BOUCLE EST HERE OR BELOW.
	{
		if (node->type == 'INPUT') // DO THE SAME FOR HERE_DOC.
		{
			file_in = open(node->content, O_RDONLY, 0644);
			// last_file = open(node->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (file_in == -1 || last_file == -1)
			{
				perror("Can't open file\n");
				exit(EXIT_FAILURE);
			}
			dup2(file_in, STDIN_FILENO);
			close(file_in);
			cmd_args = 2;
		}
		else if (node->type == 'HERE_DOC')
		{
			file_out = open(node->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (file_out)
			{
				perror("Can't open file\n");
				exit(EXIT_FAILURE);
			}
			cmd_args = 3;
			handle_here_doc(node); // Check what we've to send.
		}
		else if (node->type == 'CMD' && node->next->type == 'PIPE')
		{
			execute_pipes(node->content, char **env);
		}
		else if (node->type == 'OUTPUT')
		else if (node->type == 'APPEND')
	}
	if (last->type == 'OUTPUT')
		dup2(file_out, STDOUT_FILENO);
	exec_cmd(node->content, env);
	close(file_out);
}