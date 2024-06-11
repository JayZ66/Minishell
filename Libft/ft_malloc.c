/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:25:35 by jeguerin          #+#    #+#             */
/*   Updated: 2024/06/11 10:16:33 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

typedef struct s_reg
{
	void	**ptrs;
	int		size;
}			t_reg;

t_reg	*get_main_reg(void)
{
	static t_reg	reg = {NULL, 0};

	return (&reg);
}

void	ft_free_all(void)
{
	t_reg	*reg;
	int		i;

	i = 0;
	reg = get_main_reg();
	while (i < reg->size)
	{
		free(reg->ptrs[i]);
		i++;
	}
	free(reg->ptrs);
}

void	*ft_malloc(size_t size)
{
	t_reg	*reg;
	void	*ptr;

	reg = get_main_reg();
	ptr = malloc(size);
	if (ptr == NULL)
		return (NULL);
	reg->ptrs = realloc(reg->ptrs, (reg->size + 1) * sizeof(void *));
	if (reg->ptrs == NULL)
	{
		free(ptr);
		return (NULL);
	}
	reg->ptrs[reg->size++] = ptr;
	return (ptr);
}

// Check if ++j is ok when i = 0 !!

void	ft_free(void *ptr)
{
	t_reg	*reg;
	int		i;
	int		j;

	if (ptr == NULL)
		return ;
	reg = get_main_reg();
	i = -1;
	while (++i < reg->size)
	{
		if (reg->ptrs[i] == ptr)
		{
			free(ptr);
			j = i - 1;
			while (++j < reg->size - 1)
				reg->ptrs[j] = reg->ptrs[j + 1];
			reg->ptrs = realloc(reg->ptrs, (reg->size - 1) * sizeof(void *));
			reg->size--;
			return ;
		}
	}
	free(ptr);
	free(ptr);
}

void	*ft_realloc(void *ptr, size_t size)
{
	t_reg	*reg;
	int		i;
	void	*new_ptr;

	i = 0;
	reg = get_main_reg();
	if (ptr == NULL)
		return (ft_malloc(size));
	while (i < reg->size)
	{
		if (reg->ptrs[i] == ptr)
		{
			new_ptr = realloc(ptr, size);
			if (new_ptr == NULL)
				return (NULL);
			reg->ptrs[i] = new_ptr;
			return (new_ptr);
		}
		i++;
	}
	printf("Error: trying to realloc a non-allocated pointer\n");
	return (NULL);
}
