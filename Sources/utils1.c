/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 18:00:07 by marvin            #+#    #+#             */
/*   Updated: 2024/04/13 18:00:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (size <= 0)
		return (perror("Can't concatenate\n"), NULL);
	while (dst[i])
		i++;
	while (src[j] && j < size)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst);
}

// void	print_lst(t_token *token)
// {
// 	t_token	*tmp;

// 	tmp = token;
// 	while (tmp)
// 	{
// 		printf("Chaque node content : %s\n", tmp->content);
// 		printf("Chaque node type content : %u\n", tmp->type);
// 		tmp = tmp->next;
// 	}
// }

void	print_new_env(t_minishell *minishell)
{
	size_t	i;

	i = 0;
	while (minishell->env[i])
	{
		printf("Voici mon new env. : %s\n", minishell->env[i]);
		i++;
	}
}

int	ft_strncmp_limiter(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	while (i < n && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (i == n && s1[i] == '\n' && s1[i + 1] == '\0')
		return (0);
	else
		return (1);
}

void	print_tab(char **cmd_line)
{
	size_t	i;

	i = 0;
	while (cmd_line[i])
	{
		printf("Voici ma ligne de cmd : %s\n", cmd_line[i]);
		i++;
	}
}
