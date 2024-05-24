/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 13:20:52 by marvin            #+#    #+#             */
/*   Updated: 2024/04/01 13:20:52 by marvin           ###   ########.fr       */
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
			exit(EXIT_FAILURE); // Code exit !!
		}
		i++;
	}
	return (count_char);
}

void	exit_special_char(char **args, t_minishell *minishell)
{
	printf("bash: exit: %s: numeric argument required\n", args[1]);
	minishell->last_exit_status = EXIT_FAILURE;
	exit(EXIT_FAILURE); // Code exit !
}

char	**is_char_ok(char **args, t_minishell *minishell)
{
	size_t	i;
	size_t	j;
	size_t	count_char;

	count_char = 0;
	if (args[1])
		count_char = check_char_exit(args);
	if (count_char > 1)
		exit_special_char(args, minishell);
	else
	{
		i = -1;
		j = 1;
		while (args[1][++i])
		{
			if (args[1][i] != '-' && args[1][i] != '+')
			{
				args[1][j] = args[1][i];
				j++;
			}
		}
	}
	return (args);
}

void	builtin_exit(char **args, t_minishell *exit_code,
	t_minishell *minishell)
{
	size_t	i;
	int		exit_status;

	(void) minishell;
	i = 0;
	exit_status = 0;
	if (args[1] != NULL)
	{
		args = is_char_ok(args, minishell);
		if (args == NULL)
			return ;
		if (args[2] != NULL)
		{
			printf("-bash: exit: too many arguments\n");
			return ;
		}
		while (args[1][i])
		{
			if (ft_isdigit(args[1][i]) == 0)
			{
				printf("bash: exit: %s: numeric argument required\n", args[1]);
				exit_code->last_exit_status = 255;
				printf("exit\n");
				exit(255);
			}
			i++;
		}
		exit_status = ft_atoi(args[1]);
		exit_code->last_exit_status = exit_status;
		if (exit_status >= 0 && exit_status <= 255)
		{
			printf("exit\n");
			exit(exit_status);
		}
	}
	else if (ft_strcmp(args[0], "exit") != 0)
		printf("%s: command not found\n", args[0]);
	else
	{
		exit_code->last_exit_status = 0;
		printf("exit\n");
		exit(0);
	}
}

void	builtin_pwd(void)
{
	char	buffer[1024];
	char	*absolute_path;

	absolute_path = getcwd(buffer, sizeof(buffer));
	if (absolute_path != NULL)
		printf("The absolute path is : %s\n", absolute_path);
	else
	{
		perror("Can't get the absolute path\n");
		exit(EXIT_FAILURE);
	}
}

void	check_unset_errors(char **var)
{
	if (ft_strcmp(var[0], "unset") != 0)
		printf("%s: command not found\n", var[0]);
}

void	builtin_unset(char **var, t_minishell *minishell)
{
	size_t	i;
	size_t	j;

	j = 0;
	if (var[1])
	{
		while (var[++j])
		{
			i = -1;
			if (identifier_errors_unset(var[j]) == 1)
				if (var[j + 1] == NULL)
					break ;
			while (minishell->env[++i])
			{
				if (ft_strncmp(minishell->env[i], var[j],
						ft_strlen(var[j])) == 0
					&& minishell->env[i][ft_strlen(var[j])] == '=')
				{
					while (minishell->env[i + 1])
					{
						minishell->env[i] = minishell->env[i + 1];
						i++;
					}
					minishell->env[i] = NULL;
				}
			}
		}
	}
	check_unset_errors(var);
}

void	builtin_env(t_minishell *minishell)
{
	size_t	i;

	i = 0;
	while (minishell->env[i])
	{
		ft_printf("%s\n", minishell->env[i]);
		i++;
	}
}
