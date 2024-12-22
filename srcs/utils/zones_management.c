/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zones_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 11:05:37 by ealgar-c          #+#    #+#             */
/*   Updated: 2024/12/22 12:56:08 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_malloc.h"


/**
 * @brief Get the actual size we want to allocate at first
 * 
 * @param expected_alloc_size result of the requested allocation plus the real size of the zone metadata
 * @return size_t 
 */
size_t	get_alloc_size(size_t expected_alloc_size) {
	if (expected_alloc_size < TINY_SIZE)
		return (TINY_SIZE);
	if (expected_alloc_size < SMALL_SIZE)
		return (SMALL_SIZE);
	return (expected_alloc_size);
}

/**
 * @brief Get the real size of the zone needed
 * 
 * @param req_alloc_size base size of the allocation requested
 * @return size_t amount of bytes needed for the allocation
 */
size_t	get_zone_size(size_t req_alloc_size) {
	size_t	allocation_size = get_alloc_size(sizeof(t_alloc_zone) + req_alloc_size);
	if (malloc_utils.pages_size == -1)
		malloc_utils.pages_size = getpagesize();
	size_t new_zone_size;

	if (sizeof(t_alloc_zone) + req_alloc_size <= SMALL_SIZE) {
		new_zone_size = (ALLOCS_NB / (malloc_utils.pages_size / allocation_size) + 1) *  malloc_utils.pages_size;
		if (new_zone_size - ALLOCS_NB * allocation_size < sizeof(t_alloc_zone))
			new_zone_size += malloc_utils.pages_size;
	}
	else {
		new_zone_size = (allocation_size / malloc_utils.pages_size + 1) * malloc_utils.pages_size;
		if (new_zone_size - allocation_size < sizeof(t_alloc_zone))
			new_zone_size += malloc_utils.pages_size;
	}

	return (new_zone_size);
}

/**
 * @brief Create a new zone object
 * 
 * @param total_zone_size Size of the zone
 * @return t_alloc_zone* Pointer to the beggining of the zone created
 */
t_alloc_zone *create_new_allocating_zone(size_t total_zone_size) {
	t_alloc_zone	*new_zone;

	new_zone = mmap(NULL, total_zone_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	new_zone->zone_size = total_zone_size;
	new_zone->zone_blocks = NULL;
	new_zone->next = NULL;

	return (new_zone);
}


/**
 * @brief calculates the size already taken in a zone
 * 
 * @param zone Pointer to the zone
 * @return size_t, Size already taken in the @param zone zone
 */
size_t get_already_taken_size(t_alloc_zone *zone) {
	size_t			acum_size;
	t_zone_block	*tmp_block_ptr;

	acum_size = sizeof(t_alloc_zone);
	if (zone->zone_blocks) {
		tmp_block_ptr = zone->zone_blocks;
		while (tmp_block_ptr) {
			acum_size += tmp_block_ptr->block_size;
			tmp_block_ptr = tmp_block_ptr->next;
		}
	}
	return (acum_size);
}