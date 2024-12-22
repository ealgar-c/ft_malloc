/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 11:55:04 by ealgar-c          #+#    #+#             */
/*   Updated: 2024/12/22 13:00:19 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_malloc.h"

/**
 * @brief Creates a new block
 * 
 * @param starting_addr Memory address where the block starts
 * @param block_size Size of the new block
 * @param next Pointer to the next block of the lsit
 * @return t_zone_block* New block
 */
t_zone_block	*create_new_block(void	*starting_addr, size_t block_size, void *next) {
	t_zone_block	*block = starting_addr;

	block->block_size = block_size;
	block->next = next;
	return (block);
}

/**
 * @brief Searches a place for the new block and calls the create_new_block func to create it
 * 
 * @param zone Zone where we want to add the new block
 * @param block_size Size of the block
 * @return t_zone_block* Memory address where the new block is located
 */
t_zone_block	*create_and_add_new_block(t_alloc_zone *zone, size_t block_size) {
	// WIP, Come back soon
}

/**
 * @brief Adds the new block of memory to the @param zone zone
 * 
 * @param zone Zone where we want to add the new block
 * @param requested_size Requested size of the bock
 * @return void* Memory address where the new block is located
 */
void	*new_block_in_zone(t_alloc_zone *zone, size_t requested_size) {
	size_t	block_size = requested_size + sizeof(t_zone_block);
	t_zone_block	*new_block = NULL;

	if (!zone->zone_blocks) {
		new_block = create_new_block((void *)zone + sizeof(t_alloc_zone), block_size, NULL);
		zone->zone_blocks = new_block;
	}
	else {
		size_t taken_size = get_already_taken_size(zone);
		if (zone->zone_size - taken_size > block_size)
			new_block = create_and_add_new_block(zone, block_size);
	}
}