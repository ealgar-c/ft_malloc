/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 20:44:30 by ealgar-c          #+#    #+#             */
/*   Updated: 2025/07/05 14:19:33 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_malloc.h"

void	free(void *ptr) {
	t_alloc_zone	*actual_zone;

	if (!ptr)
		return ;
	actual_zone = find_ptr_zone(ptr);
	if (!actual_zone)
		return ;
	remove_block(actual_zone, ptr);
	if (!actual_zone->zone_blocks)
		remove_zone(actual_zone);
}