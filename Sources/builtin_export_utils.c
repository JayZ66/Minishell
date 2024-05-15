/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:31:28 by marvin            #+#    #+#             */
/*   Updated: 2024/04/19 11:31:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Check if the var. is in the
existing environment.
*/

int	is_var_in_env(char *var, t_minishell *minishell)
{
	size_t	i;

	i = 0;
	while (minishell->env[i])
	{
		if (ft_strncmp(minishell->env[i], var, ft_strlen(var)) == 0)
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_size_env(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	sort_tab(t_minishell *minishell)
{
	size_t	i;
	char	*temp;
	char	**env;

	i = 0;
	env = minishell->env;
	while (env[i + 1])
	{
		if (env[i][0] > env[i + 1][0]
			|| (env[i][0] == env[i + 1][0] && env[i][1] > env[i + 1][1]))
		{
			temp = env[i];
			env[i] = env[i + 1];
			env[i + 1] = temp;
			i = 0;
		}
		else
			i++;
	}
}

void	modify_or_create(char **args, t_minishell *minishell, size_t i, size_t j)
{
	char	*var;
	char	*new_var;
	// char	**new_env;
	new_var = ft_substr(args[i], 0, j + 1);
	if (is_var_in_env(new_var, minishell) == 1)
	{
		var = check_value(args[i]);
		minishell->env = modify_value_env(minishell, new_var, args[i] + j + 1);
		free(new_var);
		free(var);
	}
	else
	{
		var = check_value(args[i]);
		minishell->env = create_var_env(minishell, var);
		free(var);
		free(new_var);
	}
	return ;
}

// int	main(int argc, char **argv, char **env)
// {
// 	char	*str;
// 	// char	*result;
// 	(void)argc;
// 	(void)argv;
// 	char	**new_env;
// 	new_env = realloc_env(env);
// 	// str = "'''\"Salut\"''' \"tu\" 'vas' \"''bien''\"";
// 	// str = "'\"'\"'\"OK\"'\"'\"'";
// 	// char *args[] = {"export", "LS_COLORS=OK", "PATH=KO", NULL};
// 	// char *args[] = {"export", "LOL=osef", NULL};
// 	// char *args[] = {"export", NULL};
// 	// str = "export LS_COLORS=OK PATH=KO";
// 	// str = "export";
// 	// str = "export MDR=COOL PWD=PAS.DE.COULEURS MOI=PAS_OUF OH=YOHAN";
// 	// str = "export MY_VAR=\"value with spaces\" OK=\"KO\" PATH=COOL";
// 	// result = managing_quotes(str);
// 	// result = handle_quotes(str);
// 	new_env = builtin_export(str, new_env);
// 	print_new_env(new_env);
// 	// printf("Clean string : %s\n", result);
// 	return(0);
// }

void	print_env(t_minishell *minishell)
{
	size_t	i;

	i = 0;
	sort_tab(minishell);
	while (minishell->env[i])
	{
		printf("declare -x %s\n", minishell->env[i]);
		i++;
	}
	return ;
}
