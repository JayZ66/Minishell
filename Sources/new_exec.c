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

void	pipe_error(t_minishell *exit_code)
{
	perror("pipe");
	exit_code->last_exit_status = EXIT_FAILURE;
	exit(EXIT_FAILURE);
}

void	fork_error(t_minishell *exit_code)
{
	perror("fork");
	exit_code->last_exit_status = EXIT_FAILURE;
	exit(EXIT_FAILURE);
}

void	child_pipe(int *pipefd, t_minishell *minishell, t_minishell *exit_code,
	t_final_token **current)
{
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	exec_simple_cmd(current, exit_code, minishell);
	exit_code->last_exit_status = EXIT_SUCCESS;
	exit(EXIT_SUCCESS);
}

void	parent_pipe(int *pipefd)
{
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
}

int	handle_redirections(t_final_token **current, t_minishell *minishell,
	t_minishell *exit_code)
{
	int	first_file;
	int	last_file;

	first_file = 0;
	last_file = 0;
	if (manage_pipe_output(current, minishell, exit_code) == 1)
		return (-1);
	first_file = manage_redirection_input(current, exit_code, first_file);
	if (first_file == -1)
		return (-1);
	last_file = manage_redirection_output(current, last_file, minishell);
	return (0);
}

pid_t	manage_fork(t_minishell *minishell, t_minishell *exit_code,
	t_final_token **current)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		pipe_error(exit_code);
	pid = fork();
	if (pid == -1)
		fork_error(exit_code);
	else if (pid == 0)
		child_pipe(pipefd, minishell, exit_code, current);
	else
		parent_pipe(pipefd);
	return (pid);
}

int	is_pipe_command(t_final_token **current)
{
	return (((*current)->type == CMD
			&& (((*current)->next && (*current)->next->type == PIPE)
				|| ((*current)->next && (*current)->next->next
					&& (*current)->next->next->type == PIPE))));
}

void	moove_to_next_token(t_final_token **current)
{
	if ((*current)->next && ((*current)->next->type == OUTPUT
			|| (*current)->next->type == APPEND))
		*current = (*current)->next;
	*current = (*current)->next;
}

void	wait_processes(int *pid_array, int index)
{
	int	i;

	i = -1;
	while (++i < index)
		waitpid(pid_array[i], NULL, 0);
}

int	exec_loop(t_final_token **current, t_minishell *minishell,
	t_minishell *exit_code, int should_exit)
{
	int				pid_array[1024];
	int				index;
	pid_t			pid;

	index = 0;
	while (*current)
	{
		if (handle_redirections(current, minishell, exit_code) == -1)
			break ;
		if (is_pipe_command(current))
		{
			if (ft_strncmp((*current)->content, "exit", 4) == 0)
				should_exit = 1;
			else
			{
				pid = manage_fork(minishell, exit_code, current);
				pid_array[index++] = pid; // Check if index++ works well !
			}
		}
		else if ((*current)->type == CMD)
			exec_simple_cmd(current, exit_code, minishell);
		moove_to_next_token(current);
	}
	wait_processes(pid_array, index);
	return (should_exit);
}

void	execute_commands_with_pipes_and_redirections(t_final_token **lst,
	t_minishell *minishell, t_minishell *exit_code)
{
	t_final_token	*current;
	int				should_exit;
	int				saved_stdin;
	int				saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	should_exit = 0;
	current = *lst;
	should_exit = exec_loop(&current, minishell, exit_code, should_exit);
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
		if (tmp->type == OUTPUT || tmp->type == APPEND)
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

void	type_of_cmd(t_final_token **current, t_minishell *minishell,
	t_minishell *exit_code, int last_file)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (manage_cmd_pipe(current, exit_code, last_file, minishell) == 0)
		;
	else if ((*current)->type == CMD)
	{
		exec_simple_cmd(current, exit_code, minishell);
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
	}
}

int	manage_pipe_output(t_final_token **current, t_minishell *minishell,
	t_minishell *exit_code)
{
	int	first_file;
	int	last_file;
	int	saved_stdout;

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
			type_of_cmd(current, minishell, exit_code, last_file);
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
