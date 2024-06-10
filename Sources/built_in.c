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

void	if_not_digit(char *args, size_t i, t_minishell *exit_code)
{
	if (ft_isdigit(args[i]) == 0)
	{
		printf("bash: exit: %s: numeric argument required\n", args);
		exit_code->last_exit_status = 255;
		exit(255);
	}
}

char	**is_char_ok(char **args, t_minishell *minishell)
{
	size_t	count_char;

	count_char = 0;
	if (args[1])
		count_char = check_char_exit(args);
	if (count_char > 1)
		exit_special_char(args, minishell);
	else
		args = getting_exit_code(args, minishell);
	return (args);
}

void	builtin_pwd(char *str, t_minishell *minishell)
{
	char	buffer[1024];
	char	*absolute_path;

	if (check_pwd_option(str, minishell) == 1)
		return ;
	absolute_path = getcwd(buffer, sizeof(buffer));
	if (absolute_path != NULL)
		printf("%s\n", absolute_path);
	else
	{
		perror("Can't get the absolute path\n");
		minishell->last_exit_status = EXIT_FAILURE;
		return ;
	}
}

void	builtin_env(t_minishell *minishell)
{
	size_t	i;

	i = 0;
	while (minishell->env[i])
	{
		printf("%s\n", minishell->env[i]);
		i++;
	}
}
