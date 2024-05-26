/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:19:26 by marvin            #+#    #+#             */
/*   Updated: 2024/05/05 16:19:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_commands_with_pipes_and_redirections(t_final_token **lst,
	t_minishell *minishell, t_minishell *exit_code)
{
	t_final_token	*current;
	int				pid_array[1024];
	int				index;
	int				first_file;
	int				last_file;
	int				should_exit;
	int				saved_stdin;
	int				saved_stdout;
	int				pipefd[2];
	int				i;
	pid_t			pid;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	index = 0;
	should_exit = 0;
	current = *lst;
	while (current)
	{
		last_file = 0;
		first_file = 0;
		if (manage_pipe_output(&current, minishell, exit_code) == 1)
			break ;
		first_file = manage_redirection_input(&current, exit_code, first_file);
		last_file = manage_redirection_output(&current, last_file, minishell);
		if ((current->type == CMD
				&& ((current->next && current->next->type == PIPE)
					|| (current->next && current->next->next
						&& current->next->next->type == PIPE))))
		{
			if (ft_strncmp(current->content, "exit", 4) == 0)
				should_exit = 1;
			else
			{
				if (pipe(pipefd) == -1)
				{
					perror("pipe");
					exit_code->last_exit_status = EXIT_FAILURE;
					exit(EXIT_FAILURE);
				}
				pid = fork();
				if (pid == -1)
				{
					perror("fork");
					exit_code->last_exit_status = EXIT_FAILURE;
					exit(EXIT_FAILURE);
				}
				else if (pid == 0)
				{
					close(pipefd[0]);
					dup2(pipefd[1], STDOUT_FILENO);
					close(pipefd[1]);
					exec_simple_cmd(&current, exit_code, minishell);
					exit_code->last_exit_status = EXIT_SUCCESS;
					exit(EXIT_SUCCESS);
				}
				else
				{
					close(pipefd[1]);
					dup2(pipefd[0], STDIN_FILENO);
					close(pipefd[0]);
					pid_array[index] = pid;
					index++;
				}
			}
		}
		else if (current->type == CMD)
			exec_simple_cmd(&current, exit_code, minishell);
		if (current->next && (current->next->type == OUTPUT
				|| current->next->type == APPEND))
			current = current->next;
		current = current->next;
	}
	i = -1;
	while (++i < index)
		waitpid(pid_array[i], NULL, 0);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	if (should_exit)
		builtin_or_not_builtin("exit", minishell, exit_code);
}

int	how_many_output(t_final_token **current)
{
	t_final_token	*tmp;
	char			*file;

	tmp = *current;
	while (tmp)
	{
		if (tmp->type == OUTPUT)
		{
			file = tmp->content;
			while (tmp)
			{
				if (tmp->type == CMD && ft_strschr(tmp->content, file) == 0)
					return (1);
				else if (tmp->type == INPUT
					&& ft_strcmp(file, tmp->content) == 0)
					return (1);
				tmp = tmp->next;
			}
			break ;
		}
		tmp = tmp->next;
	}
	return (0);
}

int	manage_pipe_output(t_final_token **current, t_minishell *minishell,
	t_minishell *exit_code)
{
	int	first_file;
	int	last_file;
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (how_many_output(current) == 1)
	{
		while (*current)
		{
			first_file = 0;
			last_file = 0;
			first_file = manage_redirection_input(current, exit_code,
					first_file);
			last_file = manage_redirection_output(current, last_file,
					minishell);
			if (manage_cmd_pipe(current, exit_code, last_file, minishell) == 0)
				;
			else if ((*current)->type == CMD)
			{
				exec_simple_cmd(current, exit_code, minishell);
				dup2(saved_stdin, STDIN_FILENO);
				dup2(saved_stdout, STDOUT_FILENO);
			}
			if ((*current)->next && (*current)->next->type == OUTPUT)
				*current = (*current)->next;
			*current = (*current)->next;
			dup2(saved_stdout, STDOUT_FILENO);
		}
		return (1);
	}
	else
		return (0);
}
