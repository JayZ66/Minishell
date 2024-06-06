/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:37:36 by romlambe          #+#    #+#             */
/*   Updated: 2024/06/06 11:41:45 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**allocate_new_env(size_t size_env)
{
	char	**new_env;

	new_env = (char **)ft_malloc(sizeof(char *) * (size_env + 1));
	if (!new_env)
	{
		perror("Can't create new env\n");
		exit(EXIT_FAILURE);
	}
	return (new_env);
}

char	**realloc_env(char **env)
{
	char	**new_env;
	size_t	size_env;
	size_t	i;

	size_env = 0;
	while (env[size_env])
		size_env++;
	new_env = allocate_new_env(size_env);
	i = 0;
	while (i < size_env)
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			perror("Can't duplicate env string.\n");
			while (i > 0)
				ft_free(new_env[--i]);
			ft_free(new_env);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	new_env[size_env] = NULL;
	return (new_env);
}
