/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:23:54 by marvin            #+#    #+#             */
/*   Updated: 2024/04/19 11:23:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	is_relative_path(char **cmd)
// {
// 	size_t	i;
// 	size_t	is_absolute;

// 	is_absolute = 0;
// 	if (cmd[1] != NULL)
// 	{
// 		i = 0;
// 		while (cmd[1][i])
// 		{
// 			if (cmd[1][0] == '/' && cmd[1][1]) // Check when we put just "//"
// 			{
// 				is_absolute = 1;
// 				break ;
// 			}
// 			else
// 				break ;
// 			i++;
// 		}
// 	}
// 	return (is_absolute);
// }

// // TESTER SUR MAC pour les ".." et quelles est la racine
// // que l'on doit protéger ? + Si ça fonctionne ou non !
// char	*relative_to_absolute_path(char **cmd)
// {
// 	char	cwd[1024];
// 	char	*partial_path;
// 	char	*final_path;

// 	if (getcwd(cwd, sizeof(cwd)) == NULL)
// 	{
// 		perror("Can't get the new path\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	if (ft_strcmp(cmd[1], "..") == 0
// 		&& ft_strcmp(cwd, getenv("HOME")) == 0)
// 		return (perror("Can't go higher than the root\n"), NULL);
// 	partial_path = ft_strjoin(cwd, "/");
// 	final_path = ft_strjoin(partial_path, cmd[1]);
// 	free(partial_path);
// 	return (final_path);
// }