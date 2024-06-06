/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:08:18 by jeguerin          #+#    #+#             */
/*   Updated: 2023/10/02 13:08:18 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

// char	*ft_strdup(const char *s)
// {
// 	char	*dest;
// 	size_t	i;

// 	i = ft_strlen(s);
// 	if (s == NULL)
// 		return (NULL);
// 	dest = (char *)malloc(sizeof(char) * (i + 1));
// 	if (dest == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (s[i])
// 	{
// 		dest[i] = s[i];
// 		// if (dest[i] == '\n')
// 		// 	dest[i] = '\0';
// 		i++;
// 	}
// 	dest[i] = '\0';
// 	return (dest);
// }

// char	*ft_strdup(const char *str)
// {
// 	char	*new;
// 	size_t	len;

// 	len = ft_strlen(str) + 1;
// 	new = (char *)malloc(sizeof(*new) * len);
// 	if (!new)
// 		return (NULL);
// 	return ((char *)ft_memcpy(new, str, len));
// }

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		i;

	i = 0;
	dup = ft_malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
