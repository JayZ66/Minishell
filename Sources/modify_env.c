/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:32:58 by marvin            #+#    #+#             */
/*   Updated: 2024/03/23 15:32:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Here, we're going to take the path from the env. 
We have to find the shell level "SHLVL" & change it from 1 to 2.
Then we'll send this modified env. to pipex.

No need to do a copy of env because we use the one from our main.
And we don't use getenv() who get env. var. from the "real" env.
*/

//strcmp de SHLVL=
// atoi, puis itoa puis strcpy.
void	shell_level(t_minishell *minishell)
{
	size_t	i;
	char	*level;

	i = 0;
	while (minishell->env[i])
	{
		if (ft_strncmp(minishell->env[i], "SHLVL=", 6) == 0)
		{
			level = ft_itoa(ft_atoi(minishell->env[i] + 6) + 1);
			ft_string_cpy(minishell->env[i] + 6, level);
			break ;
		}
		i++;
	}
}

// char	**change_shell_level(char **env)
// {
// 	size_t	i;
// 	size_t	j;
// 	char	*str;

// 	i = 0;
// 	while (env[i])
// 	{
// 		j = 0;
// 		while (env[i][j])
// 		{
// 			if (env[i][j] == '=')
// 			{
// 				str = ft_substr(env[i], 0, j);
// 				if (ft_strcmp(str, "SHLVL") == 0)
// 				{
// 					j++;
// 					if (env[i][j] == '1')
// 					{
// 						j++;
// 						return (ft_free(str), env);
// 					}
// 				}
// 				ft_free(str);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (perror("Can't modify shell level in env.\n"), NULL);
// }
