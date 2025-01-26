/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 21:19:49 by ealgar-c          #+#    #+#             */
/*   Updated: 2025/01/26 21:34:57 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_malloc.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		cont;
	char		*ptr_dest;
	const char	*ptr_src;

	if (!src && !dst)
		return (0);
	ptr_dest = (char *)dst;
	ptr_src = (const char *)src;
	cont = 0;
	while (cont < n)
	{
		ptr_dest[cont] = (const char)ptr_src[cont];
		cont++;
	}
	return (dst);
}

void		*realloc(void *ptr, size_t size) {
	t_alloc_zone *zone = find_ptr_zone(ptr);
	if (!zone)
		return (NULL);
	t_zone_block *block = find_block_in_zone(zone, ptr);
	if (get_alloc_size(block->block_size) == get_alloc_size(size + sizeof(t_zone_block)) && (block->block_size >= size + sizeof(t_zone_block) || (block->next && (size_t)(block->next - (void *)block) >= size + sizeof(t_zone_block)))) {
		block->block_size = size + sizeof(t_zone_block);
		return (ptr);
	}
	void	*new_alloc = malloc(size);
	if (!new_alloc)
		return NULL;
	if (block->block_size - sizeof(t_zone_block) <= size)
		new_alloc = ft_memcpy(new_alloc, ptr, block->block_size - sizeof(t_zone_block));
	else
		new_alloc = ft_memcpy(new_alloc, ptr, size);
	free(ptr);
	return (new_alloc);
}