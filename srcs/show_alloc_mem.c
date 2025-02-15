/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 22:23:31 by ealgar-c          #+#    #+#             */
/*   Updated: 2025/02/15 22:43:12 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_malloc.h"

static size_t	print_block(t_zone_block *block_tmp) {
	ft_putstr("0x");
	ft_printhexa((unsigned long)block_tmp + sizeof(t_zone_block));
	ft_putstr(" - 0x");
	ft_printhexa((unsigned long)block_tmp + block_tmp->block_size);
	ft_putstr(" : ");
	ft_putnbr(block_tmp->block_size - sizeof(t_zone_block));
	ft_putstr(" bytes\n");
	return (block_tmp->block_size - sizeof(t_zone_block));
}

static size_t	print_zone(t_alloc_zone *actual_zone) {
	size_t			zone_space = 0;
	t_zone_block	*block_tmp = actual_zone->zone_blocks;

	if (block_tmp->block_size <= TINY_SIZE) {
		ft_putstr("TINY : 0x");
	} else if (block_tmp->block_size <= SMALL_SIZE) {
		ft_putstr("SMALL : 0x");
	} else {
		ft_putstr("LARGE : 0x");
	}
	ft_printhexa((unsigned long)block_tmp + sizeof(t_zone_block));
	while (block_tmp)
	{
		zone_space += print_block(block_tmp);
		block_tmp = block_tmp->next;
	}
	return (zone_space);
}

void		show_alloc_mem(void) {
	size_t			total = 0;
	t_alloc_zone	*tmp = malloc_utils.a_zones;

	while (tmp) {
		total += print_zone(tmp);
		tmp = tmp->next;
	}
	ft_putstr("TOTAL : ");
	ft_putnbr(total);
	ft_putstr(" bytes\n");
}