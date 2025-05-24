/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zones_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 11:05:37 by ealgar-c          #+#    #+#             */
/*   Updated: 2025/05/24 12:02:14 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_malloc.h"


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
		malloc_utils.pages_size = sysconf(_SC_PAGESIZE);
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

/**
 * @brief finds the zone where the @param ptr pointer is located
 * 
 * @param ptr the pointer to find
 * @return t_alloc_zone* the zone where the pointer is located
 */
t_alloc_zone	*find_ptr_zone(void *ptr) {
	t_alloc_zone	*tmp = malloc_utils.a_zones;
	t_zone_block	*block_ptr;
	
	while (tmp) {
		block_ptr = tmp->zone_blocks;
		while (block_ptr) {
			if ((void *)block_ptr + sizeof(t_zone_block) == ptr)
				return (tmp);
			block_ptr = block_ptr->next;
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	remove_zone(t_alloc_zone *zone) {
	size_t			size = (((SMALL_SIZE + sizeof(t_zone_block)) * (ALLOCS_NB + 1)) / malloc_utils.pages_size) * malloc_utils.pages_size;
	t_alloc_zone	*prev_ptr = NULL;
	t_alloc_zone	*tmp = malloc_utils.a_zones;

	while (tmp && tmp != zone){
		prev_ptr = tmp;
		tmp = tmp->next;
	}
	
	if (prev_ptr || tmp->next || zone->zone_size < size) {
		if (!prev_ptr)
			malloc_utils.a_zones = tmp->next;
		else
			prev_ptr->next = tmp->next;
		munmap(zone, zone->zone_size);
	}
	
}
