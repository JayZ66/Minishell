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

void	exec_cmd_with_fork(char *cmd, t_minishell *minishell)
{
	char	**cmd_line;
	int		pid;

	cmd_line = ft_split(cmd, ' ');
	if (!cmd_line)
	{
		minishell->last_exit_status = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Can't fork\n");
		free_tab(cmd_line);
		minishell->last_exit_status = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		child_cmd_only(cmd_line, minishell, cmd);
	else
		parent_cmd_only(pid, minishell);
	free_tab(cmd_line);
}

void	exec_absolute_path(char **cmd_line, char *cmd, t_minishell *minishell)
{
	char	*new_cmd;
	size_t	j;
	size_t	i;

	new_cmd = (char *)ft_malloc(sizeof(char) * (ft_strlen(cmd) + 1));
	i = -1;
	j = 0;
	while (cmd[++i])
	{
		if (cmd[i] != ' ')
			new_cmd[j++] = cmd[i];
		else
			break ;
	}
	new_cmd[j] = '\0';
	if (ft_strncmp(new_cmd, "./minishell", 11) == 0)
		shell_level(minishell);
	if (execve(new_cmd, cmd_line, minishell->env) == -1)
	{
		free_tab(cmd_line);
		ft_free(new_cmd);
		printf("bash: %s: command not found\n", cmd);
		minishell->last_exit_status = 127;
		exit(EXIT_FAILURE);
	}
}

void	exec_relative_path(char **cmd_line, t_minishell *minishell)
{
	char	*final_path;

	final_path = get_path(cmd_line[0], minishell);
	if (!final_path)
	{
		free_tab(cmd_line);
		minishell->last_exit_status = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
	if (execve(final_path, cmd_line, minishell->env) == -1)
	{
		free_tab(cmd_line);
		ft_free(final_path);
		minishell->last_exit_status = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
}

void	child_cmd_only(char **cmd_line, t_minishell *minishell, char *cmd)
{
	if (is_absolute_path(cmd_line) == 0)
		exec_relative_path(cmd_line, minishell);
	else if (is_absolute_path(cmd_line) == 1)
		exec_absolute_path(cmd_line, cmd, minishell);
}

void	parent_cmd_only(int pid, t_minishell *minishell)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		minishell->last_exit_status = WEXITSTATUS(status);
	else
		minishell->last_exit_status = -1;
}
