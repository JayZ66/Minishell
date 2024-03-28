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

#include "minishell.h"

/*
Here, we're going to take the path from the env. 
We have to find the shell level "SHLVL" & change it from 1 to 2.
Then we'll send this modified env. to pipex.
*/

char	**change_shell_level(char **env)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j])
		{
			if (env[i][j] == '=')
			{
				str = ft_substr(env[i], 0, j);
				if (ft_strcmp(str, "SHLVL") == 0)
				{
					j++;
					if (env[i][j] == '1')
					{
						env[i][j] = '2';
						return (free(str), env);
					}
				}
				free(str);
			}
			j++;
		}
		i++;
	}
	return (perror("Can't modify shell level in env.\n"), NULL);
}

/*
La variable d'environnement "SHLVL" est utilisée pour suivre le niveau de profondeur des shells 
(interpréteurs de commandes) dans un système UNIX. Lorsque vous exécutez un nouveau shell 
(comme bash, zsh, etc.), la valeur de "SHLVL" est augmentée de 1. Cela permet de savoir combien 
de shells sont empilés les uns sur les autres.

Maintenant, en modifiant "SHLVL" de 1 à 2 dans votre environnement, vous indiquez essentiellement 
que vous avez lancé un nouveau shell à l'intérieur d'un shell existant. Cela peut se produire, 
par exemple, lorsque vous lancez votre minishell depuis un autre shell déjà ouvert sur votre système.
*/