/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:51:19 by jeguerin          #+#    #+#             */
/*   Updated: 2024/05/29 15:47:12 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	manage_input_redirection(t_final_token **current, char *node_content,
	int first_file, t_minishell *exit_code)
{
	(void)exit_code;
	first_file = open(node_content, O_RDONLY, 0644);
	if (first_file == -1)
	{
		printf("bash: %s: No such file or directory\n", node_content);
		return (first_file);
	}
	dup2(first_file, STDIN_FILENO);
	close(first_file);
	if ((*current)->next)
		*current = (*current)->next;
	return (first_file);
}

int	manage_solo_input_redirection(t_final_token **current, char *node_content,
	int first_file, t_minishell *exit_code)
{
	(void)exit_code;
	first_file = open(node_content, O_RDONLY, 0644);
	if (first_file == -1)
	{
		printf("bash: %s: No such file or directory\n", node_content);
		return (first_file);
	}
	close(first_file);
	if ((*current)->next)
		*current = (*current)->next;
	return (first_file);
}

int	manage_redirection_input(t_final_token **current,
	t_minishell *exit_code, int first_file)
{
	int	alone;

	if ((*current)->type == INPUT && ((*current)->next
			&& (*current)->next->type == CMD))
		first_file = manage_input_redirection(current, (*current)->content,
				first_file, exit_code);
	else if ((*current)->type == HERE_DOC && ((*current)->next
			&& (*current)->next->type == CMD))
	{
		alone = 0;
		manage_here_doc(current, exit_code, (*current)->content, alone);
	}
	else if ((*current)->type == INPUT)
		first_file = manage_solo_input_redirection(current, (*current)->content,
				first_file, exit_code);
	else if ((*current)->type == HERE_DOC)
	{
		alone = 1;
		manage_here_doc(current, exit_code, (*current)->content, alone);
	}
	return (first_file);
}

void	manage_here_doc(t_final_token **current, t_minishell *exit_code,
	char *content, int alone)
{
	handle_here_doc(content, exit_code, alone);
	if ((*current)->next)
		*current = (*current)->next;
}
