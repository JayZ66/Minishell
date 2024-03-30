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

#include "minishell.h"


// Don't forget to handle quotes !!
// char	*get_the_var_of_env(t_token *node)
// {
// 	t_token	*tmp;
// 	char	*var_env;
// 	char	*result;
// 	size_t	i;

// 	tmp = node;
// 	while (tmp)
// 	{
// 		i = 0;
// 		while (tmp->content[i])
// 		{
// 			if (tmp->content[i] == '$')
// 			{
// 				i++;
// 				var_env = ft_substr(tmp->content + i, 0, ft_strlen(tmp->content + i));
// 				if (ft_strncmp(var_env, "PATH", 4) == 0)
// 					return (result = getenv(var_env), free(var_env), result);
// 				else if (ft_strncmp(var_env, "MANPATH", 7) == 0)
// 					return (result = getenv(var_env), free(var_env), result);
// 				else if (ft_strncmp(var_env, "SHELL", 5) == 0)
// 					return (result = getenv(var_env), free(var_env), result);
// 				else if (ft_strncmp(var_env, "NAME", 4) == 0)
// 					return (result = getenv(var_env), free(var_env), result);
// 				else if (ft_strncmp(var_env, "PWD", 3) == 0)
// 					return (result = getenv(var_env), free(var_env), result);
// 				else if (ft_strncmp(var_env, "LOGNAME", 7) == 0)
// 					return (result = getenv(var_env), free(var_env), result);
// 				else if (ft_strncmp(var_env, "HOME", 4) == 0)
// 					return (result = getenv(var_env), free(var_env), result);
// 				else if (ft_strncmp(var_env, "LANG", 4) == 0)
// 					return (result = getenv(var_env), free(var_env), result);
// 				else if (ft_strncmp(var_env, "LS_COLORS", 9) == 0)
// 					return (result = getenv(var_env), free(var_env), result);
// 				else if (ft_strncmp(var_env, "WAYLAND_DISPLAY", 16) == 0)
// 					return (result = getenv(var_env), free(var_env), result);
// 				else if (ft_strncmp(var_env, "LESSCLOSE", 9) == 0)
// 					return (result = getenv(var_env), free(var_env), result);
// 				else if (ft_strncmp(var_env, "TERM", 4) == 0)
// 					return (result = getenv(var_env), free(var_env), result);
// 				else if (ft_strncmp(var_env, "LESSOPEN", 8) == 0)
// 					return (result = getenv(var_env), free(var_env), result);
// 				else if (ft_strncmp(var_env, "USER", 4) == 0)
// 					return (result = getenv(var_env), free(var_env), result);
// 				else if (ft_strncmp(var_env, "DISPLAY", 7) == 0)
// 					return (result = getenv(var_env), free(var_env), result);
// 				else if (ft_strncmp(var_env, "SHLVL", 5) == 0)
// 					return (result = getenv(var_env), free(var_env), result);
// 				else if (ft_strncmp(var_env, "XDG_RUNTIME_DIR", 15) == 0)
// 					return (result = getenv(var_env), free(var_env), result);
// 				else if (ft_strncmp(var_env, "XDG_DATA_DIRS", 13) == 0)
// 					return (result = getenv(var_env), free(var_env), result);
// 				else if (ft_strncmp(var_env, "DBUS_SESSION_BUS_ADRESS", 23) == 0)
// 					return (result = getenv(var_env), free(var_env), result);
// 				else if (ft_strncmp(var_env, "HOSTTYPE", 8) == 0)
// 					return (result = getenv(var_env), free(var_env), result);
// 				else if (ft_strncmp(var_env, "PULSE_SERVER", 12) == 0)
// 					return (result = getenv(var_env), free(var_env), result);
// 				free(var_env);
// 			}
// 			i++;
// 		}
// 		tmp = tmp->next;
// 	}
// 	perror("Can't get this var. from the env.\n");
// 	return (NULL);
// }

// How are we managing the var. of env. ?
// How do we store these var. ?
// Ou voir pour utiliser le type des noeuds ? + Est-ce que ce sera stocké dans un noeud
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
		i = 0;
		while (tmp->content[i])
		{
			while (tmp->content[i] == ' ')
				i++;
			if (tmp->content[i] == '$')
			{
				i++;
				var_env = ft_substr(tmp->content + i, 0, ft_strlen(tmp->content + i));
				result = getenv(var_env);
				if (result == NULL)
					return(perror("This var. is not existing in the env.\n"), free(var_env), NULL);
				free(var_env);
				return (result);
			}
			i++;
		}
		tmp = tmp->next;
	}
	perror("Can't get this var.\n");
	return (NULL);
}