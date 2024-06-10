/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:52:32 by jeguerin          #+#    #+#             */
/*   Updated: 2024/06/10 15:37:02 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	manage_output_redirection(char *node_content, int last_file,
	t_minishell *minishell)
{
	last_file = open(node_content, O_WRONLY | O_CREAT
			| O_TRUNC, 0644);
	if (last_file == -1)
	{
		printf("bash: %s: No such file or directory\n", node_content);
		dup2(last_file, STDOUT_FILENO);
		minishell->last_exit_status = 2;
		return (-1);
	}
	dup2(last_file, STDOUT_FILENO);
	close(last_file);
	return (last_file);
}

int	manage_solo_output_redirection(char *node_content, int last_file,
	t_minishell *minishell)
{
	last_file = open(node_content, O_WRONLY | O_CREAT
			| O_TRUNC, 0644);
	if (last_file == -1)
	{
		printf("bash: %s: No such file or directory\n", node_content);
		dup2(last_file, STDOUT_FILENO);
		minishell->last_exit_status = 2;
		return (-1);
	}
	close(last_file);
	return (last_file);
}

int	manage_solo_append_redirection(char *node_content, int last_file,
	t_minishell *minishell)
{
	last_file = open(node_content, O_WRONLY | O_CREAT
			| O_APPEND, 0644);
	if (last_file == -1)
	{
		printf("bash: %s: No such file or directory\n", node_content);
		dup2(last_file, STDERR_FILENO);
		minishell->last_exit_status = 2;
		return (-1);
	}
	close(last_file);
	return (last_file);
}

int	manage_append_redirection(char *node_content, int last_file,
	t_minishell *minishell)
{
	last_file = open(node_content, O_WRONLY | O_CREAT
			| O_APPEND, 0644);
	if (last_file == -1)
	{
		printf("bash: %s: No such file or directory\n", node_content);
		dup2(last_file, STDERR_FILENO);
		minishell->last_exit_status = 2;
		return (-1);
	}
	dup2(last_file, STDOUT_FILENO);
	close(last_file);
	return (last_file);
}
