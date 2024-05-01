/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:01:14 by jeguerin          #+#    #+#             */
/*   Updated: 2024/05/01 10:55:52 by marvin           ###   ########.fr       */
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
