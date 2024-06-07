/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:51:39 by marvin            #+#    #+#             */
/*   Updated: 2024/06/03 13:51:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reset_var_value(char *var, t_minishell *minishell, char **env)
{
	size_t	i;
	size_t	var_len;
	char	*new_env;

	var_len = ft_strlen(var);
	new_env = (char *)ft_malloc(var_len + 1);
	if (!new_env)
	{
		perror("Memory allocation for new var. failed");
		minishell->last_exit_status = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
	ft_string_cpy(new_env, var);
	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], new_env, var_len) == 0)
		{
			ft_free(env[i]);
			env[i] = new_env;
			return ;
		}
	}
	env[i] = new_env;
	env[i + 1] = NULL;
}

char	*copy_new_value(const char *var, const char *new_value,
	t_minishell *minishell)
{
	size_t	new_var_len;
	char	*new_env;

	new_var_len = ft_strlen(var) + 1 + ft_strlen(new_value);
	new_env = (char *)ft_malloc(new_var_len + 1);
	if (!new_env)
	{
		perror("Memory allocation for new var. failed");
		minishell->last_exit_status = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
	ft_string_cpy(new_env, var);
	ft_strcat(new_env, new_value, ft_strlen(new_value));
	return (new_env);
}

void	print_echo_arg(char **cmd_with_options, t_minishell *exit_code)
{
	size_t	i;

	(void)exit_code;
	i = -1;
	while (cmd_with_options[++i])
	{
		if (ft_strcmp(cmd_with_options[i], "echo") == 0
			|| ft_strcmp(cmd_with_options[i], "/bin/echo") == 0)
			i++;
		if (ft_strschr(cmd_with_options[i], "\\n") == 0)
		{
			how_many_back_slash(cmd_with_options[i]);
			i++;
		}
		printf("%s ", cmd_with_options[i]);
		if (cmd_with_options[i + 1] == NULL)
			printf("\n");
	}
}

int	reset_existing_value(const char *var, const char *value,
	t_minishell *minishell, char ***env)
{
	char	*new_entry;

	new_entry = (char *)ft_malloc(ft_strlen(var) + ft_strlen(value) + 1);
	ft_string_cpy(new_entry, var);
	if (ft_strlen(value) != 0)
		ft_strcat(new_entry, value, ft_strlen(value));
	if (is_there_something_after_equal(new_entry, minishell) == 0)
	{
		reset_var_value((char *)var, minishell, (*env));
		ft_free(new_entry);
		return (1);
	}
	ft_free(new_entry);
	return (0);
}
