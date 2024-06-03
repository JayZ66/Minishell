/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:56:27 by marvin            #+#    #+#             */
/*   Updated: 2024/06/03 13:56:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_char_exit(char **args)
{
	int	count_char;
	int	i;

	count_char = 0;
	i = 0;
	while (args[1][i])
	{
		if (args[1][i] == '-' || args[1][i] == '+')
			count_char++;
		else if (ft_isdigit(args[1][i]) == 0 && (args[1][i] != '-'
			&& args[1][i] != '+'))
		{
			printf("bash: exit: %s: numeric argument required\n", args[1]);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (count_char);
}

void	exit_special_char(char **args, t_minishell *minishell)
{
	printf("bash: exit: %s: numeric argument required\n", args[1]);
	minishell->last_exit_status = EXIT_FAILURE;
	exit(EXIT_FAILURE);
}

char	**getting_exit_code(char **args, t_minishell *minishell)
{
	size_t	i;
	size_t	j;
	char	*temp;

	i = -1;
	j = 0;
	temp = malloc(ft_strlen(args[1]) + 1);
	if (!temp)
	{
		minishell->last_exit_status = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
	while (args[1][++i])
	{
		if (args[1][i] != '-' && args[1][i] != '+')
		{
			temp[j] = args[1][i];
			j++;
		}
	}
	temp[j] = '\0';
	free(args[1]);
	args[1] = ft_strdup(temp);
	free(temp);
	return (args);
}

void	manage_exit_with_code(char **args, t_minishell *exit_code,
	t_minishell *minishell)
{
	size_t	i;
	int		exit_status;

	i = 0;
	(void)minishell;
	exit_status = 0;
	args = is_char_ok(args, minishell);
	if (args[2] != NULL)
	{
		printf("-bash: exit: too many arguments\n");
		return ;
	}
	while (args[1][i])
	{
		if_not_digit(args[1], i, exit_code);
		i++;
	}
	exit_status = ft_atoi(args[1]);
	exit_status = exit_status % 256;
	exit_code->last_exit_status = exit_status;
	printf("exit\n");
	free_tab(args);
	exit(exit_status);
}

void	builtin_exit(char **args, t_minishell *exit_code,
	t_minishell *minishell)
{
	if (args[1] != NULL)
		manage_exit_with_code(args, exit_code, minishell);
	else if (ft_strncmp(args[0], "exit", 4) != 0)
		printf("%s: command not found\n", args[0]);
	else
	{
		exit_code->last_exit_status = 0;
		printf("exit\n");
		free_tab(args);
		exit(0);
	}
}
