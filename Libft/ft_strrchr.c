/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:51:02 by jeguerin          #+#    #+#             */
/*   Updated: 2024/05/02 14:31:35 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = (int)ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (unsigned char)c)
		{
			return ((char *)s + i);
		}
		i--;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s + i);
	return (NULL);
}
// int	ft_strnchr(const char *s, int c)
// {
// 	int	i;

// 	i = (int)ft_strlen(s);
// 	while (i >= 0)
// 	{
// 		if (s[i] == (unsigned char)c)
// 		{
// 			return (0);
// 		}
// 		i--;
// 	}
// 	return (1);
// }