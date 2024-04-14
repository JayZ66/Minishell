/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 17:59:21 by marvin            #+#    #+#             */
/*   Updated: 2024/03/29 17:59:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// How are we managing the var. of env. ?
// How do we store these var. ?
// Ou voir pour utiliser le type des noeuds ? 
// + Est-ce que ce sera stocké dans un noeud
// individuellement ou avec d'autres choses ?

char	*get_the_var_of_env(t_token *node)
{
	t_token	*tmp;
	char	*var_env;
	char	*result;
	size_t	i;

	tmp = node;
	while (tmp)
	{
		i = -1;
		while (tmp->content[++i])
		{
			while (tmp->content[i] == ' ')
				i++;
			if (tmp->content[i] == '$')
			{
				i++;
				var_env = ft_substr(tmp->content + i, 0,
						ft_strlen(tmp->content + i));
				result = getenv(var_env);
				if (result == NULL)
					return (perror("This var. is not existing in the env.\n"),
						free(var_env), NULL);
				return (free(var_env), result);
			}
		}
		tmp = tmp->next;
	}
	return (perror("Can't get this var.\n"), NULL);
}
