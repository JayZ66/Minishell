/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:01:14 by jeguerin          #+#    #+#             */
/*   Updated: 2024/05/06 17:24:08 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
		{
			return ((char *)s + i);
		}
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

int	ft_strnchr(const char *str, int c)
{
	char	*ptr;
	int		i;

	ptr = (char *)str;
	i = 0;
	while (ptr[i])
	{
		if (ptr[i] == (char)c)
			return (i);
		i++;
	}
	return (0);
}

int	ft_strschr(const char *str, char *ligne)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ligne[i] && str[i + 1] == ligne[i + 1])
			return (0);
		else if (str[i] == ligne[i] && str[i + 1] == ligne[i + 1] 
			&& str[i + 2] == ligne[i + 2])
			return (0);
		i++;
	}
	return (i);
}
