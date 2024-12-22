/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 19:34:49 by ealgar-c          #+#    #+#             */
/*   Updated: 2024/12/22 12:51:29 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_malloc.h"

t_malloc_utils malloc_utils = {-1, NULL};

/**
 * @brief Allocates memory for a desired size
 * 
 * @param size size of the requested memory slot
 * @return void*, NULL if something fails, else, the beggining of the memory slot
 */
void	*malloc(size_t size) {
	size_t total_zone_size = get_zone_size(&malloc_utils, size);

	if(malloc_utils.a_zones == NULL)
		malloc_utils.a_zones = create_new_allocating_zone(total_zone_size);
	t_alloc_zone *tmp_zone_ptr = malloc_utils.a_zones;
	void	*ret_alloc_block = NULL;
	
	while (!ret_alloc_block && tmp_zone_ptr) {
		if (total_zone_size == tmp_zone_ptr->zone_size)
			ret_alloc_block = new_block_in_zone(tmp_zone_ptr, size);
	}
	
	return (0);
}
