/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_only.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:56:09 by marvin            #+#    #+#             */
/*   Updated: 2024/04/19 11:56:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_one_cmd(char *cmd)
{
	size_t	i;
	int		is_option;

	i = 0;
	is_option = 0;
	while (cmd[i])
	{
		if (cmd[i] == ' ' && ((cmd[i + 1] >= 65 && cmd[i + 1] <= 90)
				|| (cmd[i + 1] >= 97 && cmd[i + 1] <= 122)))
		{
			is_option = 1;
			return (is_option);
		}
		i++;
	}
	return (is_option);
}

void	exec_cmd_with_fork(char *cmd, t_minishell *minishell, t_minishell *exit_code)
{
	char	**cmd_line;
	int		pid;

	cmd_line = ft_split(cmd, ' ');
	if (!cmd)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
	{
		perror("Can't fork\n");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		child_cmd_only(cmd_line, minishell, cmd);
	else
		parent_cmd_only(pid, exit_code);
}

void	child_cmd_only(char **cmd_line, t_minishell *minishell, char *cmd)
{
	char	*final_path;
	if (is_absolute_path(cmd_line) == 0)
	{
		final_path = get_path(cmd_line[0], minishell);
		if (!final_path)
		{
			free_tab(cmd_line);
			exit(EXIT_FAILURE);
		}
		if (execve(final_path, cmd_line, minishell->env) == -1)
		{
			free_tab(cmd_line);
			free(final_path);
			exit(EXIT_FAILURE);
		}
	}
	else if (is_absolute_path(cmd_line) == 1)
	{
		if (execve(cmd, cmd_line, minishell->env) == -1)
		{
			free_tab(cmd_line);
			exit(EXIT_FAILURE);
		}
	}
}

void	parent_cmd_only(int pid, t_minishell *exit_code)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit_code->last_exit_status = WEXITSTATUS(status);
	else
		exit_code->last_exit_status = -1;
}
