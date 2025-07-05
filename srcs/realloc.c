/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 21:19:49 by ealgar-c          #+#    #+#             */
/*   Updated: 2025/07/05 14:50:57 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_malloc.h"

void		*realloc(void *ptr, size_t size) {
	t_alloc_zone *zone = find_ptr_zone(ptr);
	if (!zone)
		return (NULL);
	t_zone_block *block = find_block_in_zone(zone, ptr);

	size_t new_size = size + sizeof(t_zone_block);
	if (get_alloc_size(block->block_size) == get_alloc_size(new_size) &&
		(block->block_size >= new_size || (block->next &&
		(size_t)(block->next - (void *)block) >= new_size)))
	{
		block->block_size = new_size;
		return (ptr);
	}
	if (!block->next)
	{
		void *block_end = (void *)block + block->block_size;
		void *zone_end = (void *)zone + zone->zone_size;
		size_t space_after_block = (size_t)(zone_end - block_end);

		if (space_after_block + block->block_size >= new_size)
		{
			block->block_size = new_size;
			return (ptr);
		}
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
