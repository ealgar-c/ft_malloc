/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:49:35 by ealgar-c          #+#    #+#             */
/*   Updated: 2024/12/22 13:00:58 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once


// EXTERNAL LIBS
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>

// CONSTS
#define ALLOCS_NB 100
#define TINY_SIZE 256
#define SMALL_SIZE 4096

// STRUCTS
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


// GLOBAL VARS
extern t_malloc_utils malloc_utils;
