/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:49:35 by ealgar-c          #+#    #+#             */
/*   Updated: 2024/12/22 12:25:44 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>

#define ALLOCS_NB 100
#define TINY_SIZE 256
#define SMALL_SIZE 4096

typedef struct s_zone_block{

	size_t	block_size;
	void	*next;

} t_zone_block;

typedef struct s_alloc_zone{

	size_t	zone_size;
	void	*zone_blocks;
	void	*next;

} t_alloc_zone;

typedef struct s_malloc_utils{

	int				pages_size;
	t_alloc_zone	*a_zones;

}	t_malloc_utils;

extern t_malloc_utils malloc_utils;
