/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:14:50 by romlambe          #+#    #+#             */
/*   Updated: 2024/04/05 16:16:21 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_pwd(char *str)
{
	char	buffer[1024];
	char	*absolute_path;

	if (ft_strcmp(str, "pwd") != 0)
	{
		printf("Too many arguments\n");
		exit(EXIT_FAILURE);
	}
	absolute_path = getcwd(buffer, sizeof(buffer));
	if (absolute_path != NULL)
		printf("The absolute path of the current directory is : %s\n", absolute_path);
	else
	{
		perror("Can't get the absolute path\n");
		exit(EXIT_FAILURE);
	}
}

void	builtin_env(char **env) //(gerer les options de env)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

char	*alloc_mem(char *str)
{
	size_t	i;
	char	*dest;

	i = 0;
	dest = (char *)malloc(sizeof(char) * (ft_strlen(str + i - 1)));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, str + i, ft_strlen(str + i - 1));
	return (dest);
}

void	builtin_exit(char *str)
{
	size_t	i;
	int		exit_status;
	char	*dest;

	i = 0;
	dest = NULL;
	exit_status = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			dest = alloc_mem(str);
			break;
		}
		i++;
	}
	printf("exit: %s", dest);
	i = 0;
	if (str != NULL)
	{
		while (str[i])
		{
			if (ft_isdigit(str[i]) == 1)
				break;
			i++;
		}
		exit_status = ft_atoi(str + i);
		if (exit_status >= 0 && exit_status <= 255)
		{
			printf("Exit_status : %d\n", exit_status);
			exit(exit_status);
		}
	} // Check if else is necessary for errors.
	else
		exit(0);
}

char	**builtin_unset(char **var, char **new_env) // Check later if we need to send **char ou *char
{ // Check how we can get our modify env.
	size_t	i;

	i = 0;
	while (new_env[i])
	{
		if (ft_strncmp(new_env[i], var[1], ft_strlen(var[1])) == 0 && new_env[i][ft_strlen(var[1])] == '=')
		{
			// free(new_env[i]); // Can't free bce i've an invalid pointer. So, maybe send it to the new_env ?
			while (new_env[i + 1])
			{
				new_env[i] = new_env[i + 1];
				i++;
			}
			new_env[i] = NULL;
			return (new_env);
		}
		i++;
	}
	perror("Can't find the var. to remove from the env.\n");
	return (NULL);
}
