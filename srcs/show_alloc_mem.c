/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 22:23:31 by ealgar-c          #+#    #+#             */
/*   Updated: 2025/07/05 14:40:15 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_malloc.h"

static size_t	print_block(t_zone_block *block_tmp) {
	ft_printf("%p - %p", (unsigned long)block_tmp + sizeof(t_zone_block), (unsigned long)block_tmp + block_tmp->block_size);
	ft_printf(" : %i bytes\n", block_tmp->block_size - sizeof(t_zone_block));
	return (block_tmp->block_size - sizeof(t_zone_block));
}

static size_t	print_zone(t_alloc_zone *actual_zone) {
	size_t			zone_space = 0;
	t_zone_block	*block_tmp = actual_zone->zone_blocks;

	if (((t_zone_block *)block_tmp)->block_size <= TINY_SIZE) {
		ft_printf("TINY : %p\n", actual_zone);
	} else if (((t_zone_block *)block_tmp)->block_size <= SMALL_SIZE) {
		ft_printf("SMALL : %p\n", actual_zone);
	} else {
		ft_printf("LARGE : %p\n", actual_zone );
	}
	while (block_tmp)
	{
		zone_space += print_block(block_tmp);
		block_tmp = block_tmp->next;
	}
	return (zone_space);
}

void	show_alloc_mem(void) {
	size_t			total = 0;
	t_alloc_zone	*tmp = malloc_utils.a_zones;

	while (tmp) {
		total += print_zone(tmp);
		tmp = tmp->next;
	}
	ft_printf("TOTAL : %i bytes\n", total);
}
