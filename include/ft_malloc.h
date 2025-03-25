/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:49:35 by ealgar-c          #+#    #+#             */
/*   Updated: 2025/03/23 14:35:06 by ealgar-c         ###   ########.fr       */
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

// USABLE FUNCS
void			*malloc(size_t size);
void			free(void *ptr);
void			*realloc(void *ptr, size_t size);
void			show_alloc_mem(void);

// functions declaration
size_t			get_alloc_size(size_t expected_alloc_size);
size_t			get_zone_size(size_t req_alloc_size);
t_alloc_zone	*create_new_allocating_zone(size_t total_zone_size);
size_t			get_already_taken_size(t_alloc_zone *zone);
t_alloc_zone	*find_ptr_zone(void *ptr);
void			remove_zone(t_alloc_zone *zone);

t_zone_block	*create_new_block(void	*starting_addr, size_t block_size, void *next);
t_zone_block	*create_and_add_new_block(t_alloc_zone *zone, size_t block_size);
void			*new_block_in_zone(t_alloc_zone *zone, size_t requested_size);
void			remove_block(t_alloc_zone *block_zone, void	*block_ptr);
t_zone_block	*find_block_in_zone(t_alloc_zone *zone, void *ptr);

int				ft_putstr(char *str);
void			ft_putnbr(int nb);
int				ft_printhexa(unsigned long long n);